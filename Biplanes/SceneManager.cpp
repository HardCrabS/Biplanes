#include "SceneManager.h"

SceneManager& SceneManager::get()
{
	static SceneManager sceneManagerSingleton;
	return sceneManagerSingleton;
}

void SceneManager::update(float timePerFrame)
{
	for (auto entity : mEntities)
	{
		entity->update(timePerFrame);
	}
}

void SceneManager::addEntity(const std::shared_ptr<Entity> entity)
{
	mEntities.push_back(entity);
}

std::vector<std::shared_ptr<Entity>> SceneManager::getEntities() const
{
	return mEntities;
}
