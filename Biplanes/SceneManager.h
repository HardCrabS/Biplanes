#pragma once
#include <vector>
#include <memory>
#include "Entity.h"

class SceneManager
{
public:
	static SceneManager& get();
	void update(float timePerFrame);
	template<typename T, typename... Args>
	static std::shared_ptr<T> createEntity(Args&&... args);
	void addEntity(const std::shared_ptr<Entity> entity);
	std::vector<std::shared_ptr<Entity>> getEntities() const;
private:
	std::vector<std::shared_ptr<Entity>> mEntities;
};

template<typename T, typename ...Args>
inline std::shared_ptr<T> SceneManager::createEntity(Args&& ...args)
{
	std::shared_ptr<T> entity = std::make_shared<T>(std::forward<Args>(args)...);
	SceneManager::get().addEntity(entity);
	return entity;
}
