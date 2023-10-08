#include "Plane.h"
#include "MathUtilities.inl"

#include <iostream>

Plane::Plane(const sf::Texture& planeTexture, sf::Texture* bulletTexture, const sf::Vector2f& viewSize)
	: mPlaneSprite(planeTexture)
	, mBulletTexture(bulletTexture)
	, mViewSize(viewSize)
{
	setScale(sf::Vector2f(1.f, 1.f) * 3.f);
	sf::FloatRect bounds = mPlaneSprite.getLocalBounds();
	mPlaneSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mVelocity = SPEED;
	mVelocityDirection = sf::Vector2f(0.f, 0.f);
	setPosition(100.f, 100.f);
	double radians = getRotation() * 3.14159 / 180;
	mGasDirection = sf::Vector2f(cos(radians), sin(radians));
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (auto& bullet : mBullets)
	{
		target.draw(bullet, states);
	}
	states.transform *= getTransform();
	target.draw(mPlaneSprite, states);
}

void Plane::update(float timePerFrame)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		gas();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		steer(-1);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		steer(1);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		sf::Time timeSinceLastShot = mLastShotClock.getElapsedTime();
		if (timeSinceLastShot.asSeconds() >= mTimePerShot)
		{
			shoot();
			mLastShotClock.restart();
		}
	}

	processMovement(timePerFrame);

	for (auto& bullet : mBullets)
	{
		bullet.update(timePerFrame);
	}
}

void Plane::gas()
{
	// TODO: this is for test only
	mVelocity = MAX_SPEED;
}

void Plane::steer(int direction)
{
	rotate(STEER_SPEED_IN_DEGREES * direction);
	double radians = getRotation() * 3.14159 / 180;
	mGasDirection = sf::Vector2f(cos(radians), sin(radians));
}

void Plane::processMovement(float timePerFrame)
{
	if (getPosition().y < 10)
	{
		mVelocityDirection = GRAVITY_DIR;
		mVelocity = -MAX_SPEED;
	}

	move(mVelocityDirection * abs(mVelocity) * timePerFrame);

	float gasToGravityAngleCos = (mGasDirection.x * GRAVITY_DIR.x + mGasDirection.y * GRAVITY_DIR.y) / (magnitude(mGasDirection) * magnitude(GRAVITY_DIR));
	mVelocity += SPEED + gasToGravityAngleCos * MASS * GRAVITY;

	mVelocityDirection = mVelocity > 0 ? mGasDirection : GRAVITY_DIR;
	mVelocityDirection = normalized(mVelocityDirection);

	if (mVelocity < -MAX_SPEED)
		mVelocity = -MAX_SPEED;
	if (mVelocity > MAX_SPEED)
		mVelocity = MAX_SPEED;
}

void Plane::shoot()
{
	Bullet bullet(*mBulletTexture, mGasDirection);
	bullet.setPosition(getPosition());
	bullet.setScale(sf::Vector2f(1.f, 1.f) * 5.f);
	mBullets.push_back(bullet);
}