#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Game.h"
#include "ResourcesManager.h"
#include "Constants.h"


Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Biplanes")
{
	DEFINE_LOGGER("main")
	LogInfo("Game Start!");
	ResourcesManager::getInstance().load();

	mSceneRoot = std::make_unique<Entity>();
	std::unique_ptr<Plane> playerPlane = std::make_unique<Plane>(
		ResourcesManager::getInstance().getTexture(ResourceID::BluePlane), mWindow.getView().getSize(), Team::Blue
	);
	playerPlane->setParent(mSceneRoot.get());
	mPlayerController.setPlane(playerPlane.get());
	std::unique_ptr<Plane> enemyPlane = std::make_unique<Plane>(
		ResourcesManager::getInstance().getTexture(ResourceID::RedPlane), mWindow.getView().getSize(), Team::Red
	);
	enemyPlane->setParent(mSceneRoot.get());
	enemyPlane->mirror();
	enemyPlane->setPosition(sf::Vector2f(600.f, 100.f));
	mAI.setPlayer(&mPlayerController);
	mAI.setPlane(enemyPlane.get());
	mSceneRoot->addChild(std::move(playerPlane));
	mSceneRoot->addChild(std::move(enemyPlane));

	mBGSprite = sf::Sprite(ResourcesManager::getInstance().getTexture(ResourceID::Background));
	auto texture = mBGSprite.getTexture();
	mBGSprite.setScale(sf::Vector2f(WINDOW_SIZE.x / texture->getSize().x, WINDOW_SIZE.y / texture->getSize().y));
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
	mAI.update(timePerFrame);
	mSceneRoot->update(timePerFrame);
	mSceneRoot->clampToBounds(sf::Vector2f(WINDOW_SIZE.x, WINDOW_SIZE.y));
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

	mPrevFrameCollisionPairs = mCollisionPairs;
}

sf::FloatRect Game::getViewBounds()
{
	auto view = mWindow.getView();
	return sf::FloatRect(view.getCenter() - view.getSize() / 2.f, view.getSize());
}
