#pragma once
#include <memory>
#include "Plane.h"

class Player
{
public:
	Player() {}
	void update(float fixedTime);
	void setPlane(std::shared_ptr<Plane> plane);
private:
	std::shared_ptr<Plane> mPlane;
};