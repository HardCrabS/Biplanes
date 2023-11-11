#pragma once
#include <memory>
#include "Plane.h"
#include "events/Dispatcher.h"
#include "events/Event.h"

class Player
{
public:
	Player();
	void update(float fixedTime);
	void setPlane(Plane* plane);
	sf::Vector2f getPosition();
private:
	void onPlaneDestroyed(const Event& event);
private:
	DECLARE_LOGGER
	Plane* mPlane;
};