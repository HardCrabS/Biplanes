#include "Bullet.h"
#include "Utils.h"
#include "ResourcesManager.h"

Bullet::Bullet(sf::Vector2f direction, Team team) 
	: Entity(ResourcesManager::getInstance().getTexture(ResourceID::Bullet), team)
	, mDirection(direction)
{
	setName("Bullet");
}

void Bullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	auto p = getPosition();
	auto s = getScale();

	states.transform *= getTransform();

	target.draw(mMainSprite, states);
	drawBoundingBox(target, states);
}

void Bullet::update(float timePerFrame)
{
	Entity::update(timePerFrame);
	move(mDirection * mSpeed * timePerFrame);
}

void Bullet::onCollisionEnter(Entity* collision)
{
	collision->takeDamage();
	LogInfo(teamToString(mTeam) + " bullet hit " + teamToString(collision->getTeam()) + " entity!")
}

void Bullet::onOutOfBounds(sf::Vector2f bounds)
{
	destroy();
}
