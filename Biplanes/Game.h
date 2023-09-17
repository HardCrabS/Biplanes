#pragma once
#include <SFML/Graphics.hpp>


class Game
{
public:
	Game();
	void run();
	void handleEvents();
	void update();
	void render();
private:
	sf::RenderWindow mWindow;
	sf::Texture mPlaneTexture;
};


void main()
{
	Game game;
	game.run();
}