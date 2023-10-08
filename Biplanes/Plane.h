#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.h"

const float MAX_SPEED = 500.f;
const float SPEED = 200.f;
const float MASS = 23.f;
const float STEER_SPEED_IN_DEGREES = 10.f;
const float GRAVITY = 10.f;
const sf::Vector2f GRAVITY_DIR = sf::Vector2f(0.f, 1.f);


class Plane : public sf::Transformable, public sf::Drawable
{
public:
	Plane() : mVelocity() {};
	Plane(const sf::Texture& planeTexture, sf::Texture* bulletTexture, const sf::Vector2f& viewSize);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float timePerFrame);
	void gas();
	void steer(int direction);
private:
	void processMovement(float timePerFrame);
	void shoot();

	sf::Sprite mPlaneSprite;
	sf::Texture* mBulletTexture;
	sf::Vector2f mViewSize;

	float mVelocity;
	sf::Vector2f mGasDirection;
	sf::Vector2f mVelocityDirection;

	std::vector<Bullet> mBullets;
	sf::Clock mLastShotClock;
	float mTimePerShot = 0.5f;
};