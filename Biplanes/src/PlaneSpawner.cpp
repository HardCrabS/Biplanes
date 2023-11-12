#include "PlaneSpawner.h"
#include "Utils.h"

PlaneSpawner::PlaneSpawner(const sf::Vector2f& viewSize, Entity* sceneRoot) 
	: mSceneRoot(sceneRoot)
	, mViewSize(viewSize)
{
	DEFINE_LOGGER("main")
	LogInfo("PlaneSpawner created!")
	mBlueSpawnPos = sf::Vector2f(100, 410);
	mRedSpawnPos = sf::Vector2f(600.f, 100.f);
}

void PlaneSpawner::startListening()
{
	Dispatcher::subscribe(EventID::EntityDestroyed, std::bind(&PlaneSpawner::onPlaneDestroyed, this, std::placeholders::_1));
	Dispatcher::subscribe(EventID::RequestPlane, std::bind(&PlaneSpawner::onRequestPlane, this, std::placeholders::_1));
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
}

void PlaneSpawner::onPlaneDestroyed(const Event& event)
{
	//const EntityDestroyedEvent& entityEvent = static_cast<const EntityDestroyedEvent&>(event);
	//if (entityEvent.entity->getTag() == "plane") {
	//	auto team = entityEvent.entity->getTeam();
	//	if (!isCatapulted(team) && !isSpawned(team)) {
	//		LogInfo("[PlaneSpawner] Plane of team " + teamToString(team) + " is destroyed, respawning.")
	//		spawnPlane(team);
	//	}
	//}
}

void PlaneSpawner::onRequestPlane(const Event& event)
{
	const RequestPlaneEvent& hangarReached = static_cast<const RequestPlaneEvent&>(event);
	LogInfo("[PlaneSpawner] Request to spawn " + teamToString(hangarReached.team) + " plane.")
	spawnPlane(hangarReached.team);
}
