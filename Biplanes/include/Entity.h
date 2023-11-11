#pragma once
#include <memory>
#include <vector>
#include <thread>
#include <set>
#include <string>
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include "Constants.h"


enum class EntityState
{
	Active,
	Destroyed
};

class Entity : public sf::Transformable, public sf::Drawable
{
public:
	Entity();
	Entity(const sf::Texture& texture, Team team = Team::None);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual void update(float timePerFrame);
	void addChild(std::unique_ptr<Entity> child);
	void setParent(Entity* parent) { mParent = parent; }
	Entity* getParent() { return mParent != nullptr ? mParent : this; }
	void destroy(float duration = 0.f);
	void removeDestroyed();
	void setState(EntityState state) { mState = state; }
	EntityState getState() { return mState; }
	Team getTeam() { return mTeam; }
	void setTag(std::string name) { mTag = std::move(name); }
	const std::string& getTag() const { return mTag; }
	virtual void clampToBounds(sf::Vector2f bounds);
	virtual void onOutOfBounds(sf::Vector2f bounds);
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
	DECLARE_LOGGER
private:
	std::vector<std::unique_ptr<Entity>> mChildren{};
	Entity* mParent = nullptr;
	EntityState mState = EntityState::Active;
	std::string mTag;
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