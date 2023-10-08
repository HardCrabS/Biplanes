#include <SFML/Graphics.hpp>
#include "Game.h"


Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Biplanes")
{
	if (mPlaneTexture.loadFromFile("./Assets/redPlane.png"))
	{
		mBulletTexture.loadFromFile("./Assets/bullet.png");
		mPlayer = Plane(mPlaneTexture, &mBulletTexture, mWindow.getView().getSize());
	}
	if (mBGTexture.loadFromFile("./Assets/background.png"))
	{
		mBGSprite = sf::Sprite(mBGTexture);
		auto size = mBGTexture.getSize();
		mBGSprite.setScale(sf::Vector2f(WINDOW_SIZE.x / size.x, WINDOW_SIZE.y / size.y));
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	while (mWindow.isOpen())
	{
		handleEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > TIME_PER_FRAME)
		{
			timeSinceLastUpdate -= TIME_PER_FRAME;
			handleEvents();
			update(TIME_PER_FRAME.asSeconds());
		}
		render();
	}
}

void Game::handleEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			mWindow.close();

	}
}

void Game::update(float timePerFrame)
{
	mPlayer.update(timePerFrame);

	auto playerPos = mPlayer.getPosition();
	if (playerPos.x > mWindow.getView().getSize().x)
	{
		mPlayer.setPosition(0, playerPos.y);
	}
	else if (playerPos.x < 0)
	{
		mPlayer.setPosition(mWindow.getView().getSize().x, playerPos.y);
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mBGSprite);
	mWindow.draw(mPlayer);
	mWindow.display();
}
