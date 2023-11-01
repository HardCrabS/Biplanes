#include "Plane.h"
#include "MathUtilities.inl"


Plane::Plane(const sf::Texture& planeTexture, sf::Texture* bulletTexture, const sf::Vector2f& viewSize, Team team)
	: Entity(planeTexture, team)
	, mBulletTexture(bulletTexture)
	, mViewSize(viewSize)
	, mCurrHealth(mMaxHealth)
{
	setScale(sf::Vector2f(1.f, 1.f) * 3.f);
	sf::FloatRect bounds = mMainSprite.getLocalBounds();
	mMainSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mVelocity = SPEED;
	mVelocityDirection = sf::Vector2f(0.f, 0.f);
	setPosition(100.f, 100.f);
	double radians = getRotation() * 3.14159 / 180;
	mGasDirection = sf::Vector2f(cos(radians), sin(radians));
	setName("Plane");
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw(target, states);

	states.transform *= getTransform();
	target.draw(mMainSprite, states);

	drawBoundingBox(target, states);
}

void Plane::update(float timePerFrame)
{
	Entity::update(timePerFrame);
	processMovement(timePerFrame);
}

void Plane::gas(bool isPressed)
{
	// toggle velocity, this is for test only
	mVelocity = isPressed ? MAX_SPEED : 0;
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

	mVelocityDirection = mVelocity >= 0 ? mGasDirection : GRAVITY_DIR;
	mVelocityDirection = normalized(mVelocityDirection);

	if (mVelocity < -MAX_SPEED)
		mVelocity = -MAX_SPEED;
	if (mVelocity > MAX_SPEED)
		mVelocity = MAX_SPEED;
}

bool Plane::isShootAllowed()
{
	sf::Time timeSinceLastShot = mLastShotClock.getElapsedTime();
	return timeSinceLastShot.asSeconds() >= mTimePerShot;
}

void Plane::shoot()
{
	if (!isShootAllowed())
		return;

	auto bullet = std::make_unique<Bullet>(*mBulletTexture, mGasDirection, Team::Red);
	bullet->setPosition(getPosition());
	bullet->setScale(sf::Vector2f(1.f, 1.f) * 5.f);
	bullet->destroy(2.f);
	this->addChild(std::move(bullet));

	mLastShotClock.restart();
}

void Plane::takeDamage()
{
	mCurrHealth -= 1;
	if (mCurrHealth <= 0)
		die();
}

void Plane::die()
{
	destroy();
}
