#pragma once
#include "Entity.h"
#include "Animation.h"
#include "ResourcesManager.h"

const int SMOKE_HEALTH = 2;
const int FIRE_HEALTH = 1;

class FireEffect : public Entity
{
public:
	FireEffect() {}
	FireEffect(Entity* parent) : mParent(parent) {
		mFireAnimation = Animation(ResourcesManager::getInstance().getSequence(ResourceID::Sequence_DamageFire), 0.1f, true);
		mFireAnimation.setScale(sf::Vector2f(3, 3));
	}
	void update(float timePerFrame) {
		mFireAnimation.update(timePerFrame);
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= mParent->getTransform();
		target.draw(mFireAnimation, states);
	}
private:
	Entity* mParent{};
	Animation mFireAnimation;
};

class SmokeEffect : public Entity
{
public:
	SmokeEffect(Entity* parent) : mParent(parent) {}
	void update(float timePerFrame) {
		Entity::update(timePerFrame);

		if (mTimeSinceLastSpawn > mSmokeSpawnRate) {
			auto smokeEntity = std::make_unique<Animation>(ResourcesManager::getInstance().getSequence(ResourceID::Sequence_DamageSmoke), 0.1f, false);
			smokeEntity->setPosition(mParent->getPosition());
			smokeEntity->setScale(sf::Vector2f(3, 3));
			mParent->addChild(std::move(smokeEntity));
			mTimeSinceLastSpawn = 0;
		}

		mTimeSinceLastSpawn += timePerFrame;
	}
private:
	Entity* mParent;
	float mSmokeSpawnRate = 0.2f;
	float mTimeSinceLastSpawn = 0;
};

class DamageEffects : public Entity
{
public:
	DamageEffects() {}
	DamageEffects(Entity* parent) : mParent(parent) {}
	void onHealthChanged(int health);
private:
	Entity* mParent{};
	Entity* mActiveEffect{};
};