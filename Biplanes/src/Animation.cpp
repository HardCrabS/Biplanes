#include "Animation.h"

Animation::Animation(std::vector<sf::Texture>& textures, float timeBetweenFrames, bool isLooping)
	: mTimeBetweenFrames(timeBetweenFrames)
	, mIsLooping(isLooping)
{
	for (auto& texture : textures) {
		mSprites.push_back(sf::Sprite(texture));
	}
	setMainSprite(mSprites[0]);
}

void Animation::set(std::vector<sf::Texture>& textures, float timeBetweenFrames, bool isLooping)
{
	mTimeBetweenFrames = timeBetweenFrames;
	mIsLooping = isLooping;

	for (auto& texture : textures) {
		mSprites.push_back(sf::Sprite(texture));
	}
	setMainSprite(mSprites[0]);
}

void Animation::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(mMainSprite, states);
}

void Animation::update(float deltaTime)
{
	if (mTimeSinceLastFrame > mTimeBetweenFrames) {
		if (mCurrentSpriteIndex == mSprites.size()) {
			if (!mIsLooping) {
				destroy();
				return;
			}
			else
				mCurrentSpriteIndex = 0;
		}
		setMainSprite(mSprites[mCurrentSpriteIndex]);
		mCurrentSpriteIndex++;
		mTimeSinceLastFrame = 0;
	}
	mTimeSinceLastFrame += deltaTime;
}

void Animation::setMainSprite(sf::Sprite& sprite)
{
	mMainSprite = sprite;
	sf::FloatRect bounds = mMainSprite.getLocalBounds();
	mMainSprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}
