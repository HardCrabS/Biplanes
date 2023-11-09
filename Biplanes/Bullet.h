#pragma once
#include "SFML/Graphics.hpp"
#include "Entity.h"
#include "Logger.h"
#include "Constants.h"

class Bullet : public Entity
{
public:
	Bullet(sf::Vector2f direction, Team team);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float timePerFrame);
	virtual void onCollisionEnter(Entity* collision);
	void onOutOfBounds(sf::Vector2f bounds) override;

private:
	sf::Vector2f mDirection;
	float mSpeed = 1000.f;
};