#include "Player.h"
#pragma once

void Player::update(float fixedTime)
{
#ifdef MANUAL_VELOCITY
	mPlane->gas(sf::Keyboard::isKeyPressed(sf::Keyboard::W));
#endif // MANUAL_VELOCITY

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		mPlane->steer(-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		mPlane->steer(1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		mPlane->shoot();
	}
}

void Player::setPlane(std::shared_ptr<Plane> plane)
{
	mPlane = plane;
}
