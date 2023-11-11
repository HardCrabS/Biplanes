#include "AI.h"
#include "MathUtilities.inl"

AI::AI() : mPlayer(), mPlane() 
{ 
	DEFINE_LOGGER("main")
	Dispatcher::subscribe(EventID::EntityDestroyed, std::bind(&AI::onPlaneDestroyed, this, std::placeholders::_1));
	Dispatcher::subscribe(EventID::BoardPlane, std::bind(&AI::onBoardPlane, this, std::placeholders::_1));
};

void AI::update(float deltaTime)
{
	if (mPlane == nullptr || !mPlayer->isAlive())
		return;

	mPlane->gas();
	sf::Vector2f AItoPlayerDirection = normalized(mPlayer->getPosition() - mPlane->getPosition());
	sf::Vector2f faceDirection = mPlane->getFaceDirection();
	float faceAngle = atan2(faceDirection.y, faceDirection.x);
	float faceAngleInDegrees = faceAngle * 180 / 3.14;
	faceAngleInDegrees += faceAngleInDegrees > 180 ? -360 : faceAngleInDegrees < -180 ? 360 : 0;

	if (abs(abs(faceAngleInDegrees) - 90) < 20) {
		mPlane->steer(faceAngleInDegrees > 0 ? 1 : -1);
	}

	float angleBetween = atan2(AItoPlayerDirection.y, AItoPlayerDirection.x) - faceAngle;
	float angleBetweenInAngles = angleBetween * 180 / 3.14;
	angleBetweenInAngles += angleBetweenInAngles > 180 ? -360 : angleBetweenInAngles < -180 ? 360 : 0;

	if (abs(angleBetweenInAngles) < 90)
	{
		//if (abs(angleBetweenInAngles) > 30) {
		//	mPlane->steer(angleBetweenInAngles > 0 ? 1 : -1);
		//}
		mPlane->shoot();
	}
}

void AI::onPlaneDestroyed(const Event& event)
{
	const EntityDestroyedEvent& entityEvent = static_cast<const EntityDestroyedEvent&>(event);
	if (mPlane == entityEvent.entity) {
		LogInfo("[AI] Plane is destroyed.")
			mPlane = nullptr;
	}
}

void AI::onBoardPlane(const Event& event)
{
	const BoardPlaneEvent& boardEvent = static_cast<const BoardPlaneEvent&>(event);
	if (boardEvent.plane->getTeam() == Team::Red) {
		mPlane = boardEvent.plane;
	}
}