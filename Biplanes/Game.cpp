#include <SFML/Graphics.hpp>
#include "Game.h"


Game::Game() : mWindow(sf::VideoMode(500, 500), "Biplanes")
{
	if (mPlaneTexture.loadFromFile("./redPlane.png"))
	{

	}
}

void Game::run()
{
	while (mWindow.isOpen())
	{
		handleEvents();
		update();
		render();
	}
}

void Game::handleEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{

	}
}

void Game::update()
{
}

void Game::render()
{
}
