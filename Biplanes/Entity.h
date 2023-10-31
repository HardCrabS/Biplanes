#pragma once
#include <memory>
#include <vector>
#include <thread>
#include <set>
#include <string>
#include <SFML/Graphics.hpp>
#include "Constants.h"


enum class EntityState
{
	Active,
	Destroyed
};

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	Entity() {}
	Entity(const sf::Texture& texture, Team team) : mMainSprite(texture), mTeam(team) {}
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update(float timePerFrame);
	void addChild(std::unique_ptr<Entity> child);
	void destroy(float duration = 0.f);
	void removeDestroyed();
	void setState(EntityState state) { mState = state; }
	EntityState getState() { return mState; }
	void setName(std::string name) { mName = std::move(name); }
	virtual void takeDamage() {};

	void fillCollisionPairs(Entity& entityRoot, std::set<std::pair<Entity*, Entity*>>& collisionPairs);
	virtual void onCollisionEnter(Entity* collision);
protected:
	virtual sf::FloatRect getBoundingRect() const;
	void drawBoundingBox(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	bool collidesWith(const Entity& entity);
	bool isCollisionBetween(Entity& le, Entity& re);
	void checkCollisionWithEveryEntity(Entity& entityToCheck, std::set<std::pair<Entity*, Entity*>>& collisionPairs);

protected:
	sf::Sprite mMainSprite;
	Team mTeam;
private:
	std::vector<std::unique_ptr<Entity>> mChildren;
	EntityState mState = EntityState::Active;
	std::string mName;
};

class DestroyManager
{
public:
	static void destroy(Entity* entity, float duration = 0.f)
	{
		if (duration > 0.f)
		{
			std::thread([entity, duration]() {
				std::this_thread::sleep_for(std::chrono::duration<float>(duration));
				entity->setState(EntityState::Destroyed);
				}
			).detach();
		}
		else
			entity->setState(EntityState::Destroyed);
	}
};