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
	Ground,
	Hangar,
	Cloud,
	Airship,

	Parachute_left,
	Parachute_center,
	Parachute_right,

	Sequence_DamageFire,
	Sequence_DamageSmoke,
	Sequence_Explosion,

	Sequence_ParachutistFly,
	Sequence_ParachutistWalk,
	Sequence_ParachutistDie,

	Font_Pixel,
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
	sf::Font& getFont(ResourceID resourceID);
	std::vector<sf::Texture>& getSequence(ResourceID resourceID);

	ResourcesManager(const ResourcesManager&) = delete;
	void operator=(const ResourcesManager&) = delete;
private:
	ResourcesManager() {}
	void loadSequence(std::string sequencePath, std::vector<sf::Texture>& sequenceVector);

	std::unordered_map<ResourceID, sf::Texture> mTextures;
	std::unordered_map<ResourceID, std::vector<sf::Texture>> mSequences;
	std::unordered_map<ResourceID, sf::Font> mFonts;
};