#include "entities/Entity.h"
#include "events/Dispatcher.h"

Entity::Entity() : mTeam(Team::None)
{
	DEFINE_LOGGER("main")
}

Entity::Entity(const sf::Texture& texture, Team team) : mMainSprite(texture), mTeam(team)
{
	DEFINE_LOGGER("main")
}

void Entity::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (const std::unique_ptr<Entity>& child : mChildren)
	{
		child->draw(target, states);
	}
}

void Entity::update(float timePerFrame)
{
	for (size_t i = 0; i < mChildren.size(); i++)
	{
		mChildren[i]->update(timePerFrame);
	}

	removeDestroyed();
}

void Entity::addChild(std::unique_ptr<Entity> child)
{
	mChildren.push_back(std::move(child));
}

void Entity::destroy(float duration)
{
	Dispatcher::notify(EntityDestroyedEvent(this));
	DestroyManager::destroy(this, duration);
}

void Entity::removeDestroyed()
{
	auto destroyedStart = std::remove_if(
		mChildren.begin(),
		mChildren.end(),
		[](std::unique_ptr<Entity>& e) { return e->getState() == EntityState::Destroyed; }
	);
	int removedEntitiesCount = std::distance(destroyedStart, mChildren.end());
	if (removedEntitiesCount > 0)
	{
		mChildren.erase(
			destroyedStart,
			mChildren.end()
		);

		LogInfo("Removed entities: " + std::to_string(removedEntitiesCount))
	}
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

void Entity::onCollisionEnter(Entity* collision)
{
	LogInfo("onCollisionEnter: " + mTag)
}

void Entity::clampToBounds(sf::Vector2f bounds)
{
	auto pos = getPosition();
	if (pos.x < 0 || pos.y < 0 || pos.x > bounds.x || pos.y > bounds.y)
		onOutOfBounds(bounds);
	for (const auto& child : mChildren) {
		child->clampToBounds(bounds);
	}
}

void Entity::onOutOfBounds(sf::Vector2f bounds)
{
	LogInfo("Out of bounds!");
	auto pos = getPosition();
	float x = pos.x < 0 ? bounds.x : pos.x > bounds.x ? 0 : pos.x;
	float y = pos.y < 0 ? bounds.y : pos.y > bounds.y ? 0 : pos.y;
	setPosition(x, y);
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
