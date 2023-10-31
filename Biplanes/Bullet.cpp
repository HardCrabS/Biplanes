#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture, sf::Vector2f direction, Team team) : Entity(texture, team), mDirection(direction)
{
	setName("Bullet");
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto p = getPosition();
	auto s = getScale();

	states.transform *= getTransform();

	target.draw(mMainSprite, states);
	drawBoundingBox(target, states);
}

void Bullet::update(float timePerFrame)
{
	Entity::update(timePerFrame);
	move(mDirection * mSpeed * timePerFrame);
}

void Bullet::onCollisionEnter(Entity* collision)
{
	collision->takeDamage();
}
