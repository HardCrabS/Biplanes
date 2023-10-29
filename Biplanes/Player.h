#pragma once
#include <memory>
#include "Plane.h"

class Player
{
public:
	Player() : mPlane() {}
	void update(float fixedTime);
	void setPlane(Plane* plane);
private:
	Plane* mPlane;
};