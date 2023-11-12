#pragma once
#include "Entity.h"

class SpriteEntity : public Entity
{
public:
	SpriteEntity(const sf::Texture& texture, bool originToCenter=false) : Entity(texture) { 
		if (originToCenter) {
			sf::FloatRect bounds = mMainSprite.getLocalBounds();
			mMainSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		}
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();
		target.draw(mMainSprite, states);
		drawBoundingBox(target, states);

		Entity::draw(target, states);
	}
};