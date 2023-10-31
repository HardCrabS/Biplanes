#include "Entity.h"
#include <iostream>

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const std::unique_ptr<Entity>& child : mChildren)
	{
		child->draw(target, states);
	}
}

void Entity::update(float timePerFrame)
{
	for (std::unique_ptr<Entity>& child : mChildren)
	{
		child->update(timePerFrame);
	}

	removeDestroyed();
}

void Entity::addChild(std::unique_ptr<Entity> child)
{
	mChildren.push_back(std::move(child));
}

void Entity::destroy(float duration)
{
	DestroyManager::destroy(this, duration);
}

void Entity::removeDestroyed()
{
	auto destroyedStart = std::remove_if(
		mChildren.begin(),
		mChildren.end(),
		[](std::unique_ptr<Entity>& e) { return e->getState() == EntityState::Destroyed;}
	);
	int removedEntitiesCount = std::distance(destroyedStart, mChildren.end());
	if (removedEntitiesCount > 0)
		std::cout << "Removed entities: " << removedEntitiesCount << "\n";
	mChildren.erase(
		destroyedStart,
		mChildren.end()
	);
	for (std::unique_ptr<Entity>& child : mChildren) {
		child->removeDestroyed();
	}
}

bool Entity::collidesWith(const Entity& entity)
{
	return getBoundingRect().intersects(entity.getBoundingRect());
}

void Entity::drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::FloatRect boundingBox = getBoundingRect();
	sf::RectangleShape rect(boundingBox.getSize());
	rect.setPosition(boundingBox.left, boundingBox.top);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Red);
	rect.setOutlineThickness(1.f);

	target.draw(rect);
}

sf::FloatRect Entity::getBoundingRect() const
{
	return getTransform().transformRect(mMainSprite.getGlobalBounds());
}

bool Entity::isCollisionBetween(Entity& le, Entity& re)
{
	return le.getBoundingRect().intersects(re.getBoundingRect());
}

void Entity::onCollisionEnter(Entity* collision)
{
	std::cout << "onCollisionEnter: " + mName + "\n";
}

void Entity::fillCollisionPairs(Entity& entityRoot, std::set<std::pair<Entity*, Entity*>>& collisionPairs)
{
	checkCollisionWithEveryEntity(entityRoot, collisionPairs);

	for (const auto& child : entityRoot.mChildren)
		fillCollisionPairs(*child, collisionPairs);
}

void Entity::checkCollisionWithEveryEntity(Entity& entityToCheck, std::set<std::pair<Entity*, Entity*>>& collisionPairs)
{
	if (this != &entityToCheck && this->collidesWith(entityToCheck) && 
		mState != EntityState::Destroyed && entityToCheck.mState != EntityState::Destroyed && 
		mTeam != entityToCheck.mTeam)
		collisionPairs.insert(std::minmax(this, &entityToCheck));

	for (const auto& child : mChildren)
		child->checkCollisionWithEveryEntity(entityToCheck, collisionPairs);
}
