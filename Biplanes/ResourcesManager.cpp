#include "ResourcesManager.h"

void ResourcesManager::load()
{
	mTextures[ResourceID::RedPlane].loadFromFile("./Assets/redPlane.png");
	mTextures[ResourceID::BluePlane].loadFromFile("./Assets/bluePlane.png");
	mTextures[ResourceID::Bullet].loadFromFile("./Assets/bullet.png");
	mTextures[ResourceID::Background].loadFromFile("./Assets/background.png");
}

sf::Texture& ResourcesManager::getTexture(ResourceID resourceID)
{
	return mTextures[resourceID];
}
