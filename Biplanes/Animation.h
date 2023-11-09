#pragma once
#include <vector>
#include "SFML/Graphics.hpp"
#include "Entity.h"

class Animation : public Entity 
{
public:
	Animation(std::vector<sf::Texture>& textures, float timeBetweenFrames, bool isLooping);
	void update(float deltaTime) override;
private:
	int mCurrentSpriteIndex = 0;
	float mTimeBetweenFrames = 0;
	float mTimeSinceLastFrame = 0;
	bool mIsLooping = false;
	std::vector<sf::Sprite> mSprites;
};