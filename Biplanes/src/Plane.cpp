#include "Plane.h"
#include "MathUtilities.inl"


Plane::Plane(const sf::Texture& planeTexture, const sf::Vector2f& viewSize, Team team)
	: Entity(planeTexture, team)
	, mViewSize(viewSize)
	, mCurrHealth(mMaxHealth)
{
	setScale(sf::Vector2f(1.f, 1.f) * 3.f);
	sf::FloatRect bounds = mMainSprite.getLocalBounds();
	mMainSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
	mVelocity = 0;
	mVelocityDirection = sf::Vector2f(0.f, 0.f);
	setPosition(100.f, 100.f);
	double radians = getRotation() * 3.14159 / 180;
	mGasDirection = sf::Vector2f(1, 0);
	mDamageEffects = DamageEffects(this);
	mHadTakenOff = false;
	setTag("Plane");
}

void Plane::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	Entity::draw(target, states);

	states.transform *= getTransform();
	target.draw(mMainSprite, states);

	target.draw(mDamageEffects);
	drawBoundingBox(target, states);
}

void Plane::update(float timePerFrame)
{
	Entity::update(timePerFrame);
	mDamageEffects.setPosition(getPosition());
	mDamageEffects.update(timePerFrame);
	processMovement(timePerFrame);

	if (!isGrounded())
		mHadTakenOff = true;
	if (getPosition().y > GROUND_LEVEL + 5.f)
		die();
}

void Plane::gas()
{
	mAcceleration = ACCELERATION;
}

void Plane::brake()
{
	mAcceleration = -ACCELERATION;
}

void Plane::steer(int direction)
{
	rotate(STEER_SPEED_IN_DEGREES * direction);
	double radians = (double)STEER_SPEED_IN_DEGREES * direction * 3.14159 / 180;

	float rotatedX = mGasDirection.x * std::cos(radians) - mGasDirection.y * std::sin(radians);
	float rotatedY = mGasDirection.x * std::sin(radians) + mGasDirection.y * std::cos(radians);

	mGasDirection = sf::Vector2f(rotatedX, rotatedY);
}

void Plane::processMovement(float timePerFrame)
{
	if (getPosition().y < 10)
	{
		mVelocityDirection = GRAVITY_DIR;
		mAcceleration = -ACCELERATION;
	}

	move(mVelocityDirection * abs(mVelocity) * timePerFrame);

	float gasToGravityAngleCos = (mGasDirection.x * GRAVITY_DIR.x + mGasDirection.y * GRAVITY_DIR.y) / (magnitude(mGasDirection) * magnitude(GRAVITY_DIR));
	mAcceleration += gasToGravityAngleCos * GRAVITY;
	mVelocity += mAcceleration;

	mVelocityDirection = mVelocity >= 0 ? mGasDirection : GRAVITY_DIR;
	mVelocityDirection = normalized(mVelocityDirection);

	mVelocity = clamp(mVelocity, -MAX_SPEED, MAX_SPEED);
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

	auto bullet = std::make_unique<Bullet>(mGasDirection, mTeam);
	bullet->setPosition(getPosition());
	bullet->setScale(sf::Vector2f(1.f, 1.f) * 5.f);
	getParent()->addChild(std::move(bullet));

	mLastShotClock.restart();
}

bool Plane::isGrounded()
{
	return abs(getPosition().y - GROUND_LEVEL) < 20.f;
}

void Plane::onCollisionEnter(Entity* collision)
{
	if (collision->getTag() == "ground" && mHadTakenOff) {
		die();
	}
}

void Plane::takeDamage()
{
	mCurrHealth -= 1;
	mDamageEffects.onHealthChanged(mCurrHealth);
	if (mCurrHealth <= 0)
		die();
}

void Plane::die()
{
	mCurrHealth = 0;
	auto explosion = std::make_unique<Animation>(ResourcesManager::getInstance().getSequence(ResourceID::Sequence_Explosion), 0.1f);
	explosion->setPosition(getPosition());
	explosion->setScale(sf::Vector2f(2, 2));
	getParent()->addChild(std::move(explosion));
	destroy();
}

void Plane::mirror()
{
	auto mirroredScale = getScale();
	mirroredScale.x *= -1;
	setScale(mirroredScale);
	mGasDirection.x *= -1;
}
