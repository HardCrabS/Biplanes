#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture, sf::Vector2f direction) : Entity(texture), mDirection(direction)
{
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto p = getPosition();
	auto s = getScale();

	states.transform *= getTransform();

	target.draw(m_mainSprite, states);
	drawBoundingBox(target, states);
}

void Bullet::update(float timePerFrame)
{
	Entity::update(timePerFrame);
	move(mDirection * mSpeed * timePerFrame);
}
