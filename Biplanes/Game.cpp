#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "SceneManager.h"

Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Biplanes")
{
	mPlaneTexture.loadFromFile("./Assets/redPlane.png");
	mBulletTexture.loadFromFile("./Assets/bullet.png");
	mBGTexture.loadFromFile("./Assets/background.png");

	auto playerPlane = SceneManager::createEntity<Plane>(mPlaneTexture, &mBulletTexture, mWindow.getView().getSize());
	mPlayerController.setPlane(playerPlane);

	mBGSprite = sf::Sprite(mBGTexture);
	auto size = mBGTexture.getSize();
	mBGSprite.setScale(sf::Vector2f(WINDOW_SIZE.x / size.x, WINDOW_SIZE.y / size.y));
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
	mPlayerController.update(timePerFrame);
	SceneManager::get().update(timePerFrame);

	for (auto entity : SceneManager::get().getEntities())
	{
		std::cout << getViewBounds().intersects(entity->getBoundingRect()) << "\n";
		/*auto entityPos = entity->getPosition();
		if (entityPos.x > mWindow.getView().getSize().x)
		{
			entity->setPosition(0, entityPos.y);
		}
		else if (entityPos.x < 0)
		{
			entity->setPosition(mWindow.getView().getSize().x, entityPos.y);
		}*/
	}
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mBGSprite);
	for (auto entity : SceneManager::get().getEntities())
	{
		mWindow.draw(*entity);
	}
	mWindow.display();
}

sf::FloatRect Game::getViewBounds()
{
	auto view = mWindow.getView();
	return sf::FloatRect(view.getCenter() - view.getSize() / 2.f, view.getSize());
}
