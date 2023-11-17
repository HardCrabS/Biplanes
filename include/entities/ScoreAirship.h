#pragma once
#include "entities/SpriteEntity.h"
#include "events/Dispatcher.h"

class ScoreAirship : public SpriteEntity
{
public:
	ScoreAirship(const sf::Vector2f& dir, float speed);
	void update(float timePerFrame) override;
private:
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void onLostScore(const Event& event);
private:
	int mBlueScore = 0;
	int mRedScore = 0;
	sf::Text mBlueText;
	sf::Text mRedText;
};