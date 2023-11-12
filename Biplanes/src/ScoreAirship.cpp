#include "ScoreAirship.h"
#include "ResourcesManager.h"

ScoreAirship::ScoreAirship(const sf::Vector2f& dir, float speed) 
	: SpriteEntity(ResourcesManager::getInstance().getTexture(ResourceID::Airship), true, false)
{
	setMovement(dir, speed);

	mBlueText.setFont(ResourcesManager::getInstance().getFont(ResourceID::Font_Pixel));
	mBlueText.setString(std::to_string(mBlueScore));
	mBlueText.setCharacterSize(24);
	mBlueText.setFillColor(sf::Color::Blue);
	mBlueText.setPosition(-18, -7);
	sf::FloatRect textBounds = mBlueText.getLocalBounds();
	mBlueText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

	mRedText.setFont(ResourcesManager::getInstance().getFont(ResourceID::Font_Pixel));
	mRedText.setString(std::to_string(mRedScore));
	mRedText.setCharacterSize(24);
	mRedText.setFillColor(sf::Color::Red);
	mRedText.setPosition(34, -7);
	textBounds = mRedText.getLocalBounds();
	mRedText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);

	Dispatcher::subscribe(EventID::LostScore, std::bind(&ScoreAirship::onLostScore, this, std::placeholders::_1));
}

void ScoreAirship::update(float timePerFrame)
{
	SpriteEntity::update(timePerFrame);

	mBlueText.setString(std::to_string(mBlueScore));
	mRedText.setString(std::to_string(mRedScore));
}

void ScoreAirship::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	SpriteEntity::draw(target, states);
	states.transform.translate(getPosition());
	target.draw(mBlueText, states);
	target.draw(mRedText, states);
}

void ScoreAirship::onLostScore(const Event& event)
{
	const LostScoreEvent& scoreEvent = static_cast<const LostScoreEvent&>(event);
	if (scoreEvent.team == Team::Blue)
		mRedScore++;
	else if (scoreEvent.team == Team::Red)
		mBlueScore++;
}
