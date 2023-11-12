#pragma once
#include <memory>
#include "entities/Plane.h"
#include "events/Dispatcher.h"
#include "events/Event.h"
#include "entities/Parachutist.h"


class Player
{
public:
	Player();
	void update(float fixedTime);
	void controlPlane();
	void controlParachutist();
	void setPlane(Plane* plane);
	bool isAlive() { return mPlane != nullptr || mParachutist != nullptr; }
	sf::Vector2f getPosition();
	void setRoot(Entity* sceneRoot) { mSceneRoot = sceneRoot; }
private:
	void onEntityDestroyed(const Event& event);
	void onBoardPlane(const Event& event);
private:
	DECLARE_LOGGER
	Plane* mPlane{};
	Parachutist* mParachutist{};
	Entity* mSceneRoot;
	bool mTakeOffInitiated = false;
	bool mHasCatapulted = false;
	Team mTeam = Team::Blue;
};