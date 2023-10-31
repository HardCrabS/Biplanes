#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Constants.h"

class Bullet : public Entity
{
public:
	Bullet(sf::Texture& texture, sf::Vector2f direction, Team team);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float timePerFrame);
	virtual void onCollisionEnter(Entity* collision);

private:
	sf::Vector2f mDirection;
	float mSpeed = 1000.f;
};