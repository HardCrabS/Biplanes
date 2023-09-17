#include "Plane.h"


Plane::Plane(sf::Sprite& sprite, float initVelocityPercent) : mSprite(sprite)
{
	mVelocity = MAX_SPEED * initVelocityPercent;
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void Plane::update(float fixedTime)
{
	processMovement(fixedTime);
}

void Plane::gas(float percent)
{
	mVelocity = MAX_SPEED * percent;
}

void Plane::steer(float angle)
{
	
}

void Plane::processMovement(float fixedTime)
{
	move(mDirection * mVelocity * fixedTime);
}