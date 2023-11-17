#pragma once
#include <SFML/Graphics.hpp>
#include <set>
#include "Logger.h"
#include "Player.h"
#include "AI.h"
#include "entities/Plane.h"
#include "entities/Animation.h"
#include "PlaneSpawner.h"

const sf::Vector2i WINDOW_SIZE = sf::Vector2i(896, 688);
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

class Game
{
public:
	Game();
	void run();
private:
	void handleEvents();
	void update(float timePerFrame);
	void render();
	void handleCollisions();
	sf::FloatRect getViewBounds();
private:
	sf::RenderWindow mWindow;

	PlaneSpawner mPlaneSpawner;
	Player mPlayerController;
	AI mAI;

	sf::Sprite mBGSprite;
	
	std::unique_ptr<Entity> mSceneRoot;

	std::set<std::pair<Entity*, Entity*>> mCollisionPairs;
	std::set<std::pair<Entity*, Entity*>> mPrevFrameCollisionPairs;
};