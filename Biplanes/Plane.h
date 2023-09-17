#pragma once
#include <SFML/Graphics.hpp>

const float MAX_SPEED = 100.f;
const float GRAVITY = 10.f;


class Plane : sf::Transformable, sf::Drawable
{
public:
	Plane(sf::Sprite& sprite, float initVelocityPercent = 0.5f);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void update(float fixedTime);
	void gas(float percent);  // [0, 1f] percent of max speed
	void steer(float angle);  // steer angle in degrees
private:
	void processMovement(float fixedTime);

	sf::Sprite mSprite;
	float mVelocity;
	sf::Vector2f mDirection;
};