#include "PlaneSpawner.h"
#include "Constants.h"
#include "Utils.h"

PlaneSpawner::PlaneSpawner(const sf::Vector2f& viewSize, Entity* sceneRoot) 
	: mSceneRoot(sceneRoot)
	, mViewSize(viewSize)
{
	logInfo("PlaneSpawner created!");
	mBlueSpawnPos = sf::Vector2f(70, GROUND_LEVEL);
	mRedSpawnPos = sf::Vector2f(830.f, GROUND_LEVEL);
}

void PlaneSpawner::startListening()
{
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

void PlaneSpawner::onRequestPlane(const Event& event)
{
	const RequestPlaneEvent& hangarReached = static_cast<const RequestPlaneEvent&>(event);
	logInfo("[PlaneSpawner] Request to spawn " + teamToString(hangarReached.team) + " plane.");
	spawnPlane(hangarReached.team);
}
