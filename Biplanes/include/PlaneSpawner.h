#pragma once
#include "Plane.h"
#include "events/Dispatcher.h"


class PlaneSpawner
{
public:
	PlaneSpawner() {}
	PlaneSpawner(const sf::Vector2f& viewSize, Entity* sceneRoot);
	void startListening();
	void spawnPlane(Team team);
private:
	void onPlaneDestroyed(const Event& event);
	void onRequestPlane(const Event& event);
private:
	DECLARE_LOGGER
	Entity* mSceneRoot{};

	sf::Vector2f mViewSize;
	sf::Vector2f mRedSpawnPos;
	sf::Vector2f mBlueSpawnPos;
};