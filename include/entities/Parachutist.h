#pragma once
#include "entities/Entity.h"
#include "entities/Animation.h"

class Parachutist : public Entity
{
public:
	Parachutist(Team team, Entity* parent);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	void update(float timePerFrame) override;
	void walk(int direction);
	void onCollisionEnter(Entity* collision) override;
	void takeDamage() override;
private:
	sf::FloatRect getBoundingRect() const override;
	void updateParachute(int index);
private:
	Animation mCurrentAnimation;
	sf::Sprite mParachuteSprite;
	sf::Sprite mAllParachuteSprites[3];
	int mWalkDirection = 0;
	int mSpriteFaceDirection = 1;
	float mParachuteHorizontalSpeed = 50.f;
	float mWalkSpeed = 100.f;
	bool isGrounded = false;
};