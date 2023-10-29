#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"


class Bullet : public Entity
{
public:
	Bullet(sf::Texture& texture, sf::Vector2f direction);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float timePerFrame);

private:
	sf::Sprite mSprite;
	sf::Vector2f mDirection;
	float mSpeed = 1000.f;
};