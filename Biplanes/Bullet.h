#pragma once
#include "SFML/Graphics.hpp"


class Bullet : public sf::Sprite
{
public:
	Bullet(sf::Texture& texture, sf::Vector2f direction);
	void update(float deltaTime);

private:
	sf::Vector2f mDirection;
	float mSpeed = 1000.f;
};