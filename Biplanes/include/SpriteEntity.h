#pragma once
#include "Entity.h"

class SpriteEntity : public Entity
{
public:
	SpriteEntity(const sf::Texture& texture) : Entity(texture) {}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mMainSprite, states);
	}
};