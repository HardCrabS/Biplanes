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

	sf::Vector2f AItoPlayerDirection = normalized(mPlayer->getPosition() - mPlane->getPosition());
	sf::Vector2f faceDirection = mPlane->getFaceDirection();
	float angleBetween = atan2(AItoPlayerDirection.y, AItoPlayerDirection.x) - atan2(faceDirection.y, faceDirection.x);
	if (abs(angleBetween) > 1) {
		if (abs(angleBetween) > 0.1f) {
			mPlane->steer(angleBetween > 0 ? 1 : -1);
		}
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
