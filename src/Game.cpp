#include <SFML/Graphics.hpp>
#include <algorithm>
#include "Game.h"
#include "ResourcesManager.h"
#include "entities/SpriteEntity.h"
#include "entities/ScoreAirship.h"
#include "Constants.h"


Game::Game() : mWindow(sf::VideoMode(WINDOW_SIZE.x, WINDOW_SIZE.y), "Biplanes")
{
	logInfo("Game Start!");
	ResourcesManager::getInstance().load();

	mSceneRoot = std::make_unique<Entity>();

	mPlayerController.setRoot(mSceneRoot.get());

	// setup background sprites
	mBGSprite = sf::Sprite(ResourcesManager::getInstance().getTexture(ResourceID::Background));
	auto texture = mBGSprite.getTexture();
	mBGSprite.setScale(sf::Vector2f(float(WINDOW_SIZE.x) / texture->getSize().x, float(WINDOW_SIZE.y) / texture->getSize().y));

	auto cloud = std::make_unique<SpriteEntity>(ResourcesManager::getInstance().getTexture(ResourceID::Cloud), true, false);
	cloud->setMovement(sf::Vector2f(1, 0), 10);
	cloud->setPosition(float(WINDOW_SIZE.x) / 2, 15);
	cloud->setScale(3.7f, 3.7f);
	cloud->setTag("cloud");
	mSceneRoot->addChild(std::move(cloud));

	auto airship = std::make_unique<ScoreAirship>(sf::Vector2f(1, 0), 7);
	airship->setPosition(float(WINDOW_SIZE.x) / 4, 100.f);
	airship->setScale(3.7f, 3.7f);
	airship->setTag("airship");
	mSceneRoot->addChild(std::move(airship));

	const sf::Texture* groundTexture = &ResourcesManager::getInstance().getTexture(ResourceID::Ground);
	auto groundEntity = std::make_unique<SpriteEntity>(*groundTexture);
	groundEntity->setScale(mBGSprite.getScale());
	groundEntity->setPosition(0, WINDOW_SIZE.y - groundTexture->getSize().y * mBGSprite.getScale().y - 13);
	groundEntity->setTag("ground");
	mSceneRoot->addChild(std::move(groundEntity));

	auto hangarEntity = std::make_unique<SpriteEntity>(ResourcesManager::getInstance().getTexture(ResourceID::Hangar), true);
	hangarEntity->setPosition(float(WINDOW_SIZE.x) / 2, GROUND_LEVEL);
	hangarEntity->setScale(3.7f, 3.7f);
	hangarEntity->setTag("hangar");
	mSceneRoot->addChild(std::move(hangarEntity));

	mAI.setPlayer(&mPlayerController);

	mPlaneSpawner = PlaneSpawner(mWindow.getView().getSize(), mSceneRoot.get());
	mPlaneSpawner.startListening();
	mPlaneSpawner.spawnPlane(Team::Blue);
	mPlaneSpawner.spawnPlane(Team::Red);
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
	mSceneRoot->clampToBounds(sf::Vector2f(static_cast<float>(WINDOW_SIZE.x), static_cast<float>(WINDOW_SIZE.y)));
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
