#include "Animation.h"

Animation::Animation(std::vector<sf::Texture>& textures, float timeBetweenFrames, bool isLooping) 
	: mTimeBetweenFrames(timeBetweenFrames)
	, mIsLooping(isLooping)
{
	for (auto& texture : textures) {
		mSprites.push_back(sf::Sprite(texture));
	}
	mMainSprite = mSprites[0];
}

void Animation::update(float deltaTime)
{
	if (mTimeSinceLastFrame > mTimeBetweenFrames) {
		if (mCurrentSpriteIndex + 1 > mSprites.size() && !mIsLooping) {
			destroy();
			return;
		}
		mCurrentSpriteIndex = (mCurrentSpriteIndex + 1) % mSprites.size();
		mMainSprite = mSprites[mCurrentSpriteIndex];
	}
	mTimeSinceLastFrame += deltaTime;
}
