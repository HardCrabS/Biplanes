#pragma once
#include <SFML/Graphics.hpp>
#include "Logger.h"
#include "Player.h"
#include "Plane.h"
#include <set>

const sf::Vector2i WINDOW_SIZE = sf::Vector2i(896, 588);
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

	Logger mLogger;
	DECLARE_LOGGER

	sf::RenderWindow mWindow;
	Player mPlayerController;

	sf::Sprite mBGSprite;

	std::unique_ptr<Entity> mSceneRoot;

	std::set<std::pair<Entity*, Entity*>> mCollisionPairs;
	std::set<std::pair<Entity*, Entity*>> mPrevFrameCollisionPairs;
};

void main()
{
	Game game;
	game.run();
}