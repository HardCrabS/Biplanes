#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Entity.h"
#include "Bullet.h"
#include "Constants.h"
#include "DamageEffects.h"


const float MAX_SPEED = 400.f;
const float ACCELERATION = 19.f;
const float STEER_SPEED_IN_DEGREES = 7.f;
const float GRAVITY = 30.f;
const sf::Vector2f GRAVITY_DIR = sf::Vector2f(0.f, 1.f);

class Plane : public Entity
{
public:
	Plane() : mVelocity() {};
	Plane(const sf::Texture& planeTexture, const sf::Vector2f& viewSize, Team team);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float timePerFrame);
	void gas();
	void brake();
	void steer(int direction);
	void shoot();
	void catapult();
	bool isHadTakenOff() { return mHadTakenOff; }
	void onCollisionEnter(Entity* collision) override;
	virtual void takeDamage();
	void mirror();
	sf::Vector2f getFaceDirection() { return mGasDirection; }
private:
	void die();
	bool isGrounded();
	void processMovement(float timePerFrame);
	bool isShootAllowed();

	sf::Vector2f mViewSize;

	float mAcceleration = 0;
	float mVelocity;
	sf::Vector2f mGasDirection;
	sf::Vector2f mVelocityDirection;
	bool mHadTakenOff = false;
	bool mHadCatapulted = false;

	const int mMaxHealth = 3;
	int mCurrHealth;
	sf::Clock mLastShotClock;
	float mTimePerShot = 0.5f;
	DamageEffects mDamageEffects;
};