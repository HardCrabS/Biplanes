#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "entities/Entity.h"

class Animation : public Entity 
{
public:
	Animation() {}
	Animation(std::vector<sf::Texture>& textures, float timeBetweenFrames, bool isLooping=false);
	void set(std::vector<sf::Texture>& textures, float timeBetweenFrames, bool isLooping);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float deltaTime) override;
	void setMainSprite(sf::Sprite& sprite);
	const sf::Sprite& getMainSprite() const { return mMainSprite; }
private:
	int mCurrentSpriteIndex = 0;
	float mTimeBetweenFrames = 0;
	float mTimeSinceLastFrame = 0;
	bool mIsLooping = false;
	std::vector<sf::Sprite> mSprites;
};