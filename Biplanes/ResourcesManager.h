#pragma once
#include <unordered_map>
#include <memory>
#include "SFML/Graphics.hpp"

enum class ResourceID
{
	RedPlane,
	BluePlane,
	Bullet,
	Background,
};

class ResourcesManager
{
public:
	static ResourcesManager& getInstance()
	{
		static ResourcesManager instance;
		return instance;
	}
	void load();
	sf::Texture& getTexture(ResourceID resourceID);

	ResourcesManager(const ResourcesManager&) = delete;
	void operator=(const ResourcesManager&) = delete;
private:
	ResourcesManager() {}

	std::unordered_map<ResourceID, sf::Texture> mTextures;
};