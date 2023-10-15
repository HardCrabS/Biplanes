#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	virtual void update(float timePerFrame) {};
	void drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getBoundingRect() const;
	bool isCollitionBetween(Entity& le, Entity& re);
};
