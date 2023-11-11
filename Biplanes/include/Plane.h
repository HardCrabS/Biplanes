#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Bullet.h"
#include "Constants.h"
#include "DamageEffects.h"

//#define MANUAL_VELOCITY

#ifdef MANUAL_VELOCITY
	const float MAX_SPEED = 500.f;
	const float SPEED = 0.f;
	const float MASS = 0.f;
	const float STEER_SPEED_IN_DEGREES = 7.f;
	const float GRAVITY = 0.f;
	const sf::Vector2f GRAVITY_DIR = sf::Vector2f(0.f, 1.f);
#else
	const float MAX_SPEED = 400.f;
	const float SPEED = 200.f;
	const float MASS = 23.f;
	const float STEER_SPEED_IN_DEGREES = 7.f;
	const float GRAVITY = 10.f;
	const sf::Vector2f GRAVITY_DIR = sf::Vector2f(0.f, 1.f);
#endif

class Plane : public Entity
{
public:
	Plane() : mVelocity() {};
	Plane(const sf::Texture& planeTexture, const sf::Vector2f& viewSize, Team team);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float timePerFrame);
	void gas(bool isPressed);
	void steer(int direction);
	void shoot();
	virtual void takeDamage();
	void die();
	void mirror();
	sf::Vector2f getFaceDirection() { return mGasDirection; }
private:
	void processMovement(float timePerFrame);
	bool isShootAllowed();

	sf::Vector2f mViewSize;

	float mVelocity;
	sf::Vector2f mGasDirection;
	sf::Vector2f mVelocityDirection;

	const int mMaxHealth = 3;
	int mCurrHealth;
	sf::Clock mLastShotClock;
	float mTimePerShot = 0.5f;
	DamageEffects mDamageEffects;
};