#include "entities/Parachutist.h"
#include "ResourcesManager.h"
#include "Utils.h"
#include "events/Dispatcher.h"

Parachutist::Parachutist(Team team, Entity* parent)
{
	setScale(2, 2);
	mTeam = team;
	setParent(parent);

	mAllParachuteSprites[0] = sf::Sprite(ResourcesManager::getInstance().getTexture(ResourceID::Parachute_left));
	mAllParachuteSprites[1] = sf::Sprite(ResourcesManager::getInstance().getTexture(ResourceID::Parachute_center));
	mAllParachuteSprites[2] = sf::Sprite(ResourcesManager::getInstance().getTexture(ResourceID::Parachute_right));

	updateParachute(1);
	
	mCurrentAnimation = Animation(ResourcesManager::getInstance().getSequence(ResourceID::Sequence_ParachutistFly), 0.1f, true);

	mCurrentAnimation.setScale(1.7f, 1.7f);
	setTag("parachutist");
}

void Parachutist::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	drawBoundingBox(target, states);
	states.transform *= getTransform();
	target.draw(mCurrentAnimation, states);
	if (!isGrounded)
		target.draw(mParachuteSprite, states);
}

void Parachutist::update(float timePerFrame)
{
	sf::Vector2f horizontal = sf::Vector2f(static_cast<float>(mWalkDirection), 0) * (isGrounded ? mWalkSpeed : mParachuteHorizontalSpeed);
	sf::Vector2f vertical = sf::Vector2f(0, isGrounded ? 0.f : 70.f);
	move((horizontal + vertical) * timePerFrame);

	mCurrentAnimation.update(timePerFrame);
}

void Parachutist::walk(int direction)
{
	if (isGrounded) {
		if (direction != 0 && direction != mSpriteFaceDirection) {
			auto scale = getScale();
			scale.x *= -1;
			setScale(scale);
			mSpriteFaceDirection = direction;
		}
	}
	else {
		updateParachute(1 - direction);
	}
	mWalkDirection = direction;
}

void Parachutist::onCollisionEnter(Entity* collision)
{
	if (collision->getTag() == "ground") {
		if (!isGrounded) {
			mCurrentAnimation = Animation(ResourcesManager::getInstance().getSequence(ResourceID::Sequence_ParachutistWalk), 0.1f, true);
			mCurrentAnimation.setScale(2, 2);
			isGrounded = true;
		}
	}
	else if (collision->getTag() == "hangar") {
		//Dispatcher::notify(RequestPlaneEvent(mTeam));
		destroy();
	}
}

void Parachutist::takeDamage()
{
	auto dieAnimation = std::make_unique<Animation>(ResourcesManager::getInstance().getSequence(ResourceID::Sequence_ParachutistDie), 0.1f);
	dieAnimation->setPosition(getPosition());
	dieAnimation->setScale(sf::Vector2f(2, 2));
	mParent->addChild(std::move(dieAnimation));
	Dispatcher::notify(LostScoreEvent(mTeam));
	destroy();
}

sf::FloatRect Parachutist::getBoundingRect() const
{
	return getTransform().transformRect((
		combineRectangles(mParachuteSprite.getGlobalBounds(), mCurrentAnimation.getMainSprite().getGlobalBounds())
	));
}

void Parachutist::updateParachute(int index)
{
	mParachuteSprite = mAllParachuteSprites[index];
	mParachuteSprite.setPosition(sf::Vector2f(-9, -18.f));
}
