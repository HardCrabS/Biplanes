#include "AI.h"
#include "MathUtilities.inl"

AI::AI() : mPlayer(), mPlane() 
{ 
	DEFINE_LOGGER("main")
	Dispatcher::subscribe(EventID::EntityDestroyed,
		std::bind(&AI::onPlaneDestroyed, this, std::placeholders::_1));
};

void AI::update(float deltaTime)
{
	if (mPlane == nullptr)
		return;

	mPlane->gas();
	sf::Vector2f AItoPlayerDirection = normalized(mPlayer->getPosition() - mPlane->getPosition());
	sf::Vector2f faceDirection = mPlane->getFaceDirection();
	float faceAngle = atan2(faceDirection.y, faceDirection.x);
	float faceAngleInDegrees = faceAngle * 180 / 3.14;
	float angleBetween = atan2(AItoPlayerDirection.y, AItoPlayerDirection.x) - faceAngle;

	if (abs(angleBetween) > 0.1f) {
		mPlane->steer(angleBetween > 0 ? 1 : -1);
	}
	mPlane->shoot();
}

void AI::onPlaneDestroyed(const Event& event)
{
	if (event.getEventID() == EventID::EntityDestroyed) {
		const EntityDestroyedEvent& entityEvent = static_cast<const EntityDestroyedEvent&>(event);
		if (mPlane == entityEvent.entity) {
			LogInfo("[AI] Plane is destroyed.")
				mPlane = nullptr;
		}
	}
}
