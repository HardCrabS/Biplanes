#include "ResourcesManager.h"

void ResourcesManager::load()
{
	mTextures[ResourceID::RedPlane].loadFromFile("./Assets/redPlane.png");
	mTextures[ResourceID::BluePlane].loadFromFile("./Assets/bluePlane.png");
	mTextures[ResourceID::Bullet].loadFromFile("./Assets/bullet.png");
	mTextures[ResourceID::Background].loadFromFile("./Assets/background.png");
	mTextures[ResourceID::Ground].loadFromFile("./Assets/ground.png");
	mTextures[ResourceID::Hangar].loadFromFile("./Assets/hangar.png");

	mTextures[ResourceID::Parachute_left].loadFromFile("./Assets/sequence/Parachutist/Parachute/left.png");
	mTextures[ResourceID::Parachute_center].loadFromFile("./Assets/sequence/Parachutist/Parachute/center.png");
	mTextures[ResourceID::Parachute_right].loadFromFile("./Assets/sequence/Parachutist/Parachute/right.png");

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
		sequenceVector.push_back(sequenceTexture);
		index++;
		path = sequencePath + std::to_string(index) + ".png";
	}
}
