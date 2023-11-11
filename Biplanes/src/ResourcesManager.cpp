#include "ResourcesManager.h"

void ResourcesManager::load()
{
	mTextures[ResourceID::RedPlane].loadFromFile("./Assets/redPlane.png");
	mTextures[ResourceID::BluePlane].loadFromFile("./Assets/bluePlane.png");
	mTextures[ResourceID::Bullet].loadFromFile("./Assets/bullet.png");
	mTextures[ResourceID::Background].loadFromFile("./Assets/background.png");

	loadSequence("./Assets/sequence/DamagedSmoke/", mSequences[ResourceID::Sequence_DamageSmoke]);
	loadSequence("./Assets/sequence/DamagedFire/", mSequences[ResourceID::Sequence_DamageFire]);
	loadSequence("./Assets/sequence/Explosion/", mSequences[ResourceID::Sequence_Explosion]);
}

sf::Texture& ResourcesManager::getTexture(ResourceID resourceID)
{
	return mTextures[resourceID];
}

std::vector<sf::Texture>& ResourcesManager::getSequence(ResourceID resourceID)
{
	return mSequences[resourceID];
}

void ResourcesManager::loadSequence(std::string sequencePath, std::vector<sf::Texture>& sequenceVector)
{
	sf::Texture sequenceTexture;
	int index = 0;
	std::string path = sequencePath + std::to_string(index) + ".png";
	while (sequenceTexture.loadFromFile(path))
	{
		LogInfo("Loaded sequence texture: " + path);
		sequenceVector.push_back(sequenceTexture);
		index++;
		path = sequencePath + std::to_string(index) + ".png";
	}
}
