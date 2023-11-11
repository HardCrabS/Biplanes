#pragma once
#include <unordered_map>
#include <memory>
#include "Logger.h"
#include "SFML/Graphics.hpp"

enum class ResourceID
{
	RedPlane,
	BluePlane,
	Bullet,
	Background,
	Sequence_DamageFire,
	Sequence_DamageSmoke,
	Sequence_Explosion,
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
	std::vector<sf::Texture>& getSequence(ResourceID resourceID);

	ResourcesManager(const ResourcesManager&) = delete;
	void operator=(const ResourcesManager&) = delete;
private:
	ResourcesManager() {DEFINE_LOGGER("main")}
	void loadSequence(std::string sequencePath, std::vector<sf::Texture>& sequenceVector);

	DECLARE_LOGGER
	std::unordered_map<ResourceID, sf::Texture> mTextures;
	std::unordered_map<ResourceID, std::vector<sf::Texture>> mSequences;
};