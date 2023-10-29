#pragma once
#include <memory>
#include <vector>
#include <SFML/Graphics.hpp>

enum class EntityState
{
	Active,
	Destroyed
};

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update(float timePerFrame);
	void addChild(std::unique_ptr<Entity> child);
	void removeDestroyed();
	void drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual sf::FloatRect getBoundingRect() const;
	bool isCollitionBetween(Entity& le, Entity& re);
	EntityState getState() { return m_status; }
private:
	std::vector<std::unique_ptr<Entity>> m_children;
	EntityState m_status = EntityState::Active;
};
