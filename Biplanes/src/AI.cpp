#include "AI.h"
#include "MathUtilities.inl"
#include "Constants.h"

AI::AI() : mPlayer(), mPlane() 
{ 
	DEFINE_LOGGER("main")
	LogInfo("AI created!")
	Dispatcher::subscribe(EventID::EntityDestroyed, std::bind(&AI::onPlaneDestroyed, this, std::placeholders::_1));
	Dispatcher::subscribe(EventID::BoardPlane, std::bind(&AI::onBoardPlane, this, std::placeholders::_1));
};

void AI::update(float deltaTime)
{
	if (mPlane == nullptr || !mPlayer->isAlive())
		return;

	if (!mHadTakenOff) {
		if (mPlane->getVelocity() < 400) {
			mPlane->gas();
		}
		else {
			mPlane->steer(1);
			mHadTakenOff = (GROUND_LEVEL - mPlane->getPosition().y) > 30;
		}
		return;
	}

	mPlane->gas();
	sf::Vector2f AItoPlayerDirection = normalized(mPlayer->getPosition() - mPlane->getPosition());
	sf::Vector2f faceDirection = mPlane->getFaceDirection();
	float faceAngle = atan2(faceDirection.y, faceDirection.x);
	float faceAngleInDegrees = faceAngle * 180 / 3.14;
	faceAngleInDegrees += faceAngleInDegrees > 180 ? -360 : faceAngleInDegrees < -180 ? 360 : 0;

	bool isCloseToGround = (GROUND_LEVEL - mPlane->getPosition().y) < 90;
	bool isCloseToSky = mPlane->getPosition().y < 30;
	if (isCloseToSky || isCloseToGround) {
		if (faceAngleInDegrees < 0)  // facing sky
		{
			if (isCloseToSky) {
				mPlane->steer(faceAngleInDegrees < -90 ? -1 : 1);
				return;
			}
		}
		else  // facing ground
		{
			if (isCloseToGround) {
				mPlane->steer(faceAngleInDegrees > 90 ? 1 : -1);
				return;
			}
		}
	}

	float angleBetween = atan2(AItoPlayerDirection.y, AItoPlayerDirection.x) - faceAngle;
	float angleBetweenInAngles = angleBetween * 180 / 3.14;
	angleBetweenInAngles += angleBetweenInAngles > 180 ? -360 : angleBetweenInAngles < -180 ? 360 : 0;

	if (abs(angleBetweenInAngles) < 90)
	{
		if (abs(angleBetweenInAngles) > 30) {
			mPlane->steer(angleBetweenInAngles > 0 ? 1 : -1);
		}
		mPlane->shoot();
	}
}

void AI::onPlaneDestroyed(const Event& event)
{
	const EntityDestroyedEvent& entityEvent = static_cast<const EntityDestroyedEvent&>(event);
	if (mPlane == entityEvent.entity) {
		mPlane = nullptr;
		if (!mHasCatapulted) {
			LogInfo("[AI] Requesting new plane")
			Dispatcher::notify(RequestPlaneEvent(Team::Red));
		}
	}
}

void AI::onBoardPlane(const Event& event)
{
	const BoardPlaneEvent& boardEvent = static_cast<const BoardPlaneEvent&>(event);
	if (boardEvent.plane->getTeam() == Team::Red) {
		mPlane = boardEvent.plane;
		mHadTakenOff = false;
		mHasCatapulted = false;
	}
}