#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture, sf::Vector2f direction) : mSprite(texture), mDirection(direction)
{
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto p = getPosition();
	auto s = getScale();

	states.transform *= getTransform();

	target.draw(mSprite, states);
}

void Bullet::update(float deltaTime)
{
	move(mDirection * mSpeed * deltaTime);
}
