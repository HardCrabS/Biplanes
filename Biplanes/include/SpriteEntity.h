#pragma once
#include "Entity.h"

class SpriteEntity : public Entity
{
public:
	SpriteEntity(const sf::Texture& texture, bool originToCenter=false, bool enableCollision=true) 
		: Entity(texture)
		, mEnableCollision(enableCollision)
	{ 
		if (originToCenter) {
			sf::FloatRect bounds = mMainSprite.getLocalBounds();
			mMainSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
		}
	}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override {
		states.transform *= getTransform();
		target.draw(mMainSprite, states);
		drawBoundingBox(target, states);

		Entity::draw(target, states);
	}
	void update(float timePerFrame) override {
		if (mSpeed > 0.01f) {
			move(mMoveDirection * mSpeed * timePerFrame);
		}
	}
	sf::FloatRect getBoundingRect() const override
	{
		return mEnableCollision ? Entity::getBoundingRect() : sf::FloatRect();
	}
	void setMovement(const sf::Vector2f& dir, float speed) {
		mMoveDirection = dir;
		mSpeed = speed;
	}
private:
	sf::Vector2f mMoveDirection{};
	float mSpeed = 0;
	bool mEnableCollision = true;
};