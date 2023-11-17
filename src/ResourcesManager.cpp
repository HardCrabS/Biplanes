#include "ResourcesManager.h"
#include <filesystem>

void ResourcesManager::load()
{
	loadTexture(ResourceID::RedPlane, "Assets/redPlane.png");
	loadTexture(ResourceID::BluePlane, "Assets/bluePlane.png");
	loadTexture(ResourceID::Bullet, "Assets/bullet.png");
	loadTexture(ResourceID::Background, "Assets/background.png");
	loadTexture(ResourceID::Ground, "Assets/ground.png");
	loadTexture(ResourceID::Hangar, "Assets/hangar.png");
	loadTexture(ResourceID::Cloud, "Assets/cloud.png");
	loadTexture(ResourceID::Airship, "Assets/airship.png");

	loadTexture(ResourceID::Parachute_left, "./Assets/sequence/Parachutist/Parachute/left.png");
	loadTexture(ResourceID::Parachute_center, "./Assets/sequence/Parachutist/Parachute/center.png");
	loadTexture(ResourceID::Parachute_right, "./Assets/sequence/Parachutist/Parachute/right.png");

	mFonts[ResourceID::Font_Pixel].loadFromFile("./Assets/Fonts/Pixel.ttf");

	loadSequence("./Assets/sequence/DamagedSmoke/", mSequences[ResourceID::Sequence_DamageSmoke]);
	loadSequence("./Assets/sequence/DamagedFire/", mSequences[ResourceID::Sequence_DamageFire]);
	loadSequence("./Assets/sequence/Explosion/", mSequences[ResourceID::Sequence_Explosion]);

	loadSequence("./Assets/sequence/Parachutist/Walk/", mSequences[ResourceID::Sequence_ParachutistWalk]);
	loadSequence("./Assets/sequence/Parachutist/Fly/", mSequences[ResourceID::Sequence_ParachutistFly]);
	loadSequence("./Assets/sequence/Parachutist/Die/", mSequences[ResourceID::Sequence_ParachutistDie]);
}

sf::Texture& ResourcesManager::getTexture(ResourceID resourceID)
{
	return mTextures[resourceID];
}

sf::Font& ResourcesManager::getFont(ResourceID resourceID)
{
	return mFonts[resourceID];
}

std::vector<sf::Texture>& ResourcesManager::getSequence(ResourceID resourceID)
{
	return mSequences[resourceID];
}

void ResourcesManager::loadTexture(ResourceID rID, const std::string& path)
{
	bool success = mTextures[rID].loadFromFile(path);
	if (!success)
		throw std::runtime_error("Failed to load a texture: " + path);
}

void ResourcesManager::loadSequence(const std::string& sequencePath, std::vector<sf::Texture>& sequenceVector)
{
	sf::Texture sequenceTexture;
	int index = 0;
	//std::string path = sequencePath + std::to_string(index) + ".png";
	std::filesystem::path path{ sequencePath + std::to_string(index) + ".png" };
	while(true)
	{
		bool success = sequenceTexture.loadFromFile(path.string());
		if (!success)
			throw std::runtime_error("Failed to load a sequence texture: " + path.string());

		sequenceVector.push_back(sequenceTexture);
		index++;
		path = std::filesystem::path(sequencePath + std::to_string(index) + ".png");
		if (!std::filesystem::exists(path))
			break;
	}
}
