#include "AI.h"
#include "MathUtilities.inl"
#include "Constants.h"

AI::AI() : mPlayer(), mPlane() 
{ 
	logInfo("AI created!");
	Dispatcher::subscribe(EventID::EntityDestroyed, std::bind(&AI::onPlaneDestroyed, this, std::placeholders::_1));
	Dispatcher::subscribe(EventID::BoardPlane, std::bind(&AI::onBoardPlane, this, std::placeholders::_1));

	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	mTimeUntilChangeDirection = static_cast<float>(std::rand()) / RAND_MAX;  // [0, 1)
	mTimeUntilChangeDirection = 0.1f + mTimeUntilChangeDirection * (0.8f - 0.1f);  // Scale to (0.1, 0.8)
};

void AI::update(float deltaTime)
{
	if (mPlane == nullptr || !mPlayer->isAlive())
		return;

	if (!mHadTakenOff) {
		if (mPlane->getVelocity() < 300) {
			mPlane->gas();
		}
		else {
			mPlane->steer(1);
		}
		mHadTakenOff = (GROUND_LEVEL - mPlane->getPosition().y) > 70;
		return;
	}

	mPlane->gas();
	sf::Vector2f AItoPlayerDirection = normalized(mPlayer->getPosition() - mPlane->getPosition());
	sf::Vector2f faceDirection = mPlane->getFaceDirection();
	float faceAngle = atan2(faceDirection.y, faceDirection.x);
	float faceAngleInDegrees = faceAngle * 180 / 3.14f;
	faceAngleInDegrees += faceAngleInDegrees > 180 ? -360 : faceAngleInDegrees < -180 ? 360 : 0;

	bool isCloseToGround = (GROUND_LEVEL - mPlane->getPosition().y) < 150;
	bool isCloseToSky = mPlane->getPosition().y < 30;
	if (isCloseToSky || isCloseToGround) {
		if (faceAngleInDegrees < 0)  // facing sky
		{
			if (isCloseToSky) {
				mPlane->steer(faceAngleInDegrees < -90 ? -1 : 1);
				mLatestSteerDirection = 0;
				return;
			}
		}
		else  // facing ground
		{
			if (isCloseToGround) {
				mPlane->steer(faceAngleInDegrees > 90 ? 1 : -1);
				mLatestSteerDirection = 0;
				return;
			}
		}
	}

	float angleBetween = atan2(AItoPlayerDirection.y, AItoPlayerDirection.x) - faceAngle;
	float angleBetweenInAngles = angleBetween * 180 / 3.14f;
	angleBetweenInAngles += angleBetweenInAngles > 180 ? -360 : angleBetweenInAngles < -180 ? 360 : 0;
	mTimeSinceChanedDirection += deltaTime;

	if (abs(angleBetweenInAngles) < 20)  // player is in our sight
	{
		if (abs(angleBetweenInAngles) > 10) {
			mPlane->steer(angleBetweenInAngles > 0 ? 1 : -1);
		}
		mPlane->shoot();
	}
	else {
		// steer in a random direction for some time
		mPlane->steer(mLatestSteerDirection);
		if (mTimeSinceChanedDirection >= mTimeUntilChangeDirection) {
			mLatestSteerDirection = std::rand() % 3 - 1;

			mTimeUntilChangeDirection = static_cast<float>(std::rand()) / RAND_MAX;
			mTimeUntilChangeDirection = 0.1f + mTimeUntilChangeDirection * (0.8f - 0.1f);
			mTimeSinceChanedDirection = 0;
		}
	}
}

void AI::onPlaneDestroyed(const Event& event)
{
	const EntityDestroyedEvent& entityEvent = static_cast<const EntityDestroyedEvent&>(event);
	if (mPlane == entityEvent.entity) {
		mPlane = nullptr;
		if (!mHasCatapulted) {
			logInfo("[AI] Requesting new plane");
			Dispatcher::notify(RequestPlaneEvent(Team::Red));
		}
	}
}

void AI::onBoardPlane(const Event& event)
{
	const BoardPlaneEvent& boardEvent = static_cast<const BoardPlaneEvent&>(event);
	if (boardEvent.plane->getTeam() == Team::Red) {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		mPlane = boardEvent.plane;
		mHadTakenOff = false;
		mHasCatapulted = false;
	}
}