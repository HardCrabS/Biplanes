#include "Bullet.h"

Bullet::Bullet(sf::Texture& texture, sf::Vector2f direction) : Sprite(texture), mDirection(direction)
{
}

void Bullet::update(float deltaTime)
{
	move(mDirection * mSpeed * deltaTime);
}
