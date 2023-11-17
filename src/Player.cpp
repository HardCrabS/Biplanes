#pragma once
#include "Player.h"

Player::Player() : mPlane()
{
	logInfo("Player created!");
	Dispatcher::subscribe(EventID::EntityDestroyed, std::bind(&Player::onEntityDestroyed, this, std::placeholders::_1));
	Dispatcher::subscribe(EventID::BoardPlane, std::bind(&Player::onBoardPlane, this, std::placeholders::_1));
}

void Player::update(float fixedTime)
{
	if (mHasCatapulted)
		controlParachutist();
	else
		controlPlane();
}

void Player::controlPlane()
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
	{
		mPlane->catapult();
		auto parachutist = std::make_unique<Parachutist>(mPlane->getTeam(), mSceneRoot);
		parachutist->setPosition(mPlane->getPosition());
		mParachutist = parachutist.get();
		mSceneRoot->addChild(std::move(parachutist));
		mPlane = nullptr;
		mHasCatapulted = true;
	}
}

void Player::controlParachutist()
{
	if (mParachutist == nullptr)
		return;

	int direction = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		direction = -1;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		direction = 1;

	mParachutist->walk(direction);
}

void Player::setPlane(Plane* plane)
{
	mPlane = plane;
	mPlane = nullptr;
}

sf::Vector2f Player::getPosition()
{
	return mPlane != nullptr ? mPlane->getPosition() : mParachutist != nullptr ? mParachutist->getPosition() : sf::Vector2f(0, 0);
}

void Player::onEntityDestroyed(const Event& event)
{
	const EntityDestroyedEvent& entityEvent = static_cast<const EntityDestroyedEvent&>(event);
	bool isParachutistDeath = entityEvent.entity == mParachutist;
	if (entityEvent.entity == mPlane || isParachutistDeath) {
		mPlane = nullptr;
		mParachutist = nullptr;
		if (!mHasCatapulted || isParachutistDeath) {
			logInfo("[Player] Requesting new plane");
			Dispatcher::notify(RequestPlaneEvent(mTeam));
		}
	}
}

void Player::onBoardPlane(const Event& event)
{
	const BoardPlaneEvent& boardEvent = static_cast<const BoardPlaneEvent&>(event);
	if (boardEvent.plane->getTeam() == mTeam) {
		mPlane = boardEvent.plane;
		mTakeOffInitiated = false;
		mHasCatapulted = false;
	}
}
