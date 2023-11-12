#include "DamageEffects.h"

void DamageEffects::onHealthChanged(int health)
{
	if (health == SMOKE_HEALTH) {
		auto smokeEffect = std::make_unique<SmokeEffect>(this);
		this->addChild(std::move(smokeEffect));
	}
	else if (health == FIRE_HEALTH) {
		auto fireEffect = std::make_unique<FireEffect>(this);
		this->addChild(std::move(fireEffect));
	}
}
