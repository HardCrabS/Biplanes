#pragma once
#include <SFML/Graphics.hpp>


class Entity : public sf::Transformable, public sf::Drawable
{
public:
	void drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getBoundingRect() const;
	bool isCollitionBetween(Entity& le, Entity& re);
};