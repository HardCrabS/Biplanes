#include "Entity.h"

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
