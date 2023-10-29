#include "Entity.h"

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

void Entity::removeDestroyed()
{
	m_children.erase(
		std::remove_if(
			m_children.begin(),
			m_children.end(),
			[](std::unique_ptr<Entity>& e) { return e->getState() == EntityState::Destroyed;}),
		m_children.end()
	);
	for (std::unique_ptr<Entity>& child : m_children) {
		child->removeDestroyed();
	}
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
	return sf::FloatRect();
}

bool Entity::isCollitionBetween(Entity& le, Entity& re)
{
	return le.getBoundingRect().intersects(re.getBoundingRect());
}
