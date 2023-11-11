#include "PlaneSpawner.h"

PlaneSpawner::PlaneSpawner(const sf::Vector2f& viewSize, Entity* sceneRoot) 
	: mSceneRoot(sceneRoot)
	, mViewSize(viewSize)
{
	DEFINE_LOGGER("main")

	mBlueSpawnPos = sf::Vector2f(100, 100);
	mRedSpawnPos = sf::Vector2f(600.f, 200.f);

	Dispatcher::subscribe(EventID::EntityDestroyed, std::bind(&PlaneSpawner::onPlaneDestroyed, *this, std::placeholders::_1));
}

void PlaneSpawner::spawnPlane(Team team)
{
	ResourceID rID = team == Team::Blue ? ResourceID::BluePlane : ResourceID::RedPlane;
	std::unique_ptr<Plane> plane = std::make_unique<Plane>(
		ResourcesManager::getInstance().getTexture(rID), mViewSize, team
		);
	plane->setParent(mSceneRoot);

	sf::Vector2f pos = team == Team::Blue ? mBlueSpawnPos : mRedSpawnPos;
	plane->setPosition(pos);
	if (team == Team::Red)
		plane->mirror();

	Dispatcher::notify(BoardPlaneEvent(plane.get()));
	mSceneRoot->addChild(std::move(plane));

	//mPlayerController.setPlane(playerPlane.get());

	//std::unique_ptr<Plane> enemyPlane = std::make_unique<Plane>(
	//	ResourcesManager::getInstance().getTexture(ResourceID::RedPlane), mViewSize, team
	//	);
	//enemyPlane->setParent(mSceneRoot);
	//enemyPlane->mirror();
	//enemyPlane->setPosition(sf::Vector2f(600.f, 200.f));
	//mAI.setPlayer(&mPlayerController);
	//mAI.setPlane(enemyPlane.get());
	//mSceneRoot->addChild(std::move(enemyPlane));
}

void PlaneSpawner::onPlaneDestroyed(const Event& event)
{
	const EntityDestroyedEvent& entityEvent = static_cast<const EntityDestroyedEvent&>(event);
	if (entityEvent.entity->getTag() == "Plane")
		spawnPlane(entityEvent.entity->getTeam());
}
