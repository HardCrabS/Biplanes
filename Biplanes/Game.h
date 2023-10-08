#pragma once
#include <SFML/Graphics.hpp>
#include "Plane.h"

const sf::Vector2i WINDOW_SIZE = sf::Vector2i(896, 588);
const sf::Time TIME_PER_FRAME = sf::seconds(1.f / 60.f);

class Game
{
public:
	Game();
	void run();
	void handleEvents();
	void update(float timePerFrame);
	void render();
private:
	sf::RenderWindow mWindow;

	sf::Texture mBGTexture;
	sf::Texture mPlaneTexture;
	sf::Texture mBulletTexture;

	sf::Sprite mBGSprite;
	Plane mPlayer;
};


void main()
{
	Game game;
	game.run();
}