#pragma once
#include "Player.h"

Player::Player() : mPlane()
{
	DEFINE_LOGGER("main")
	Dispatcher::subscribe(EventID::EntityDestroyed, std::bind(&Player::onPlaneDestroyed, this, std::placeholders::_1));
	Dispatcher::subscribe(EventID::BoardPlane, std::bind(&Player::onBoardPlane, this, std::placeholders::_1));
}

void Player::update(float fixedTime)
{
	if (mPlane == nullptr)
		return;

	if (mPlane->isHadTakenOff())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			mPlane->brake();
		else
			mPlane->gas();
	}
	else if (mTakeOffInitiated) {
		mPlane->gas();
	}
	else {
		// wait for the first W press
		mTakeOffInitiated = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
		return;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		mPlane->steer(-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		mPlane->steer(1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		mPlane->shoot();
	}
}

void Player::setPlane(Plane* plane)
{
	mPlane = plane;
}

sf::Vector2f Player::getPosition()
{
	return mPlane != nullptr ? mPlane->getPosition() : sf::Vector2f(0, 0);
}

void Player::onPlaneDestroyed(const Event& event)
{
	const EntityDestroyedEvent& entityEvent = static_cast<const EntityDestroyedEvent&>(event);
	if (mPlane == entityEvent.entity) {
		LogInfo("[Player] Plane is destroyed.")
		mPlane = nullptr;
		mTakeOffInitiated = false;
	}
}

void Player::onBoardPlane(const Event& event)
{
	const BoardPlaneEvent& boardEvent = static_cast<const BoardPlaneEvent&>(event);
	if (boardEvent.plane->getTeam() == mTeam) {
		mPlane = boardEvent.plane;
	}
}
