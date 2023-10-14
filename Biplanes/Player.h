#pragma once
#include "Plane.h"


class Player
{
public:
	Player() {}
	Player(Plane* plane);
	void update(float fixedTime);
private:
	Plane* mPlane;
};