#include "Entity.h"
#include <iostream>

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const std::unique_ptr<Entity>& child : m_children)
	{
		child->draw(target, states);
	}
}

void Entity::update(float timePerFrame)
{
	for (std::unique_ptr<Entity>& child : m_children)
	{
		child->update(timePerFrame);
	}

	removeDestroyed();
}

void Entity::addChild(std::unique_ptr<Entity> child)
{
	m_children.push_back(std::move(child));
}

void Entity::destroy(float duration)
{
	DestroyManager::destroy(this, duration);
}

void Entity::removeDestroyed()
{
	m_children.erase(
		std::remove_if(
			m_children.begin(),
			m_children.end(),
			[](std::unique_ptr<Entity>& e) { return e->getState() == EntityState::Destroyed;}
		),
		m_children.end()
	);
	for (std::unique_ptr<Entity>& child : m_children) {
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
	return getTransform().transformRect(m_mainSprite.getGlobalBounds());
}

bool Entity::isCollisionBetween(Entity& le, Entity& re)
{
	return le.getBoundingRect().intersects(re.getBoundingRect());
}

void Entity::fillCollisionPairs(Entity& entityRoot, std::set<std::pair<Entity*, Entity*>>& collisionPairs)
{
	checkCollisionWithEveryEntity(entityRoot, collisionPairs);

	for (const auto& child : entityRoot.m_children)
		fillCollisionPairs(*child, collisionPairs);
}

void Entity::onCollisionEnter(Entity* collision)
{
	std::cout << "onCollisionEnter\n";
}

void Entity::onCollisionExit(Entity* collision)
{
	std::cout << "onCollisionExit\n";
}

void Entity::checkCollisionWithEveryEntity(Entity& entityToCheck, std::set<std::pair<Entity*, Entity*>>& collisionPairs)
{
	if (this != &entityToCheck && this->collidesWith(entityToCheck))
		collisionPairs.insert(std::minmax(this, &entityToCheck));

	for (const auto& child : m_children)
		child->checkCollisionWithEveryEntity(entityToCheck, collisionPairs);
}
