#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include "Game.h"

Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Biplanes")
{
	mPlaneTexture.loadFromFile("./Assets/redPlane.png");
	mEnemyPlaneTexture.loadFromFile("./Assets/bluePlane.png");
	mBulletTexture.loadFromFile("./Assets/bullet.png");
	mBGTexture.loadFromFile("./Assets/background.png");

	mSceneRoot = std::make_unique<Entity>();
	std::unique_ptr<Plane> playerPlane = std::make_unique<Plane>(mPlaneTexture, &mBulletTexture, mWindow.getView().getSize());
	mPlayerController.setPlane(playerPlane.get());
	std::unique_ptr<Plane> enemyPlane = std::make_unique<Plane>(mEnemyPlaneTexture, &mBulletTexture, mWindow.getView().getSize());
	enemyPlane->setPosition(sf::Vector2f(600.f, 100.f));
	mSceneRoot->addChild(std::move(playerPlane));
	mSceneRoot->addChild(std::move(enemyPlane));

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
	handleCollisions();

	mPlayerController.update(timePerFrame);
	mSceneRoot->update(timePerFrame);
}

void Game::render()
{
	mWindow.clear();
	mWindow.draw(mBGSprite);
	mWindow.draw(*mSceneRoot);
	mWindow.display();
}

void Game::handleCollisions()
{
	mCollisionPairs.clear();
	mSceneRoot->fillCollisionPairs(*mSceneRoot, mCollisionPairs);

	// call onCollisionEnter on entities which collided this frame
	std::set<std::pair<Entity*, Entity*>> enterCollisions;
	std::set_difference(
		mCollisionPairs.begin(), mCollisionPairs.end(),
		mPrevFrameCollisionPairs.begin(), mPrevFrameCollisionPairs.end(),
		std::inserter(enterCollisions, enterCollisions.begin())
	);
	for (const std::pair<Entity*, Entity*>& pair : enterCollisions)
	{
		pair.first->onCollisionEnter(pair.second);
		pair.second->onCollisionEnter(pair.first);
	}

	// call onCollisionExit on entities which stopped colliding this frame
	std::set<std::pair<Entity*, Entity*>> exitCollisions;
	std::set_difference(
		mPrevFrameCollisionPairs.begin(), mPrevFrameCollisionPairs.end(),
		mCollisionPairs.begin(), mCollisionPairs.end(),
		std::inserter(exitCollisions, exitCollisions.begin())
	);
	for (const std::pair<Entity*, Entity*>& pair : exitCollisions)
	{
		pair.first->onCollisionExit(pair.second);
		pair.second->onCollisionExit(pair.first);
	}

	mPrevFrameCollisionPairs = mCollisionPairs;
}

sf::FloatRect Game::getViewBounds()
{
	auto view = mWindow.getView();
	return sf::FloatRect(view.getCenter() - view.getSize() / 2.f, view.getSize());
}
