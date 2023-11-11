#include "DamageEffects.h"

void DamageEffects::onHealthChanged(int health)
{
	//if (mActiveEffect != nullptr) {
	//	mActiveEffect->destroy();
	//}
	if (health == SMOKE_HEALTH) {
		auto smokeEffect = std::make_unique<SmokeEffect>(this);
		mActiveEffect = smokeEffect.get();
		this->addChild(std::move(smokeEffect));
	}
	else if (health == FIRE_HEALTH) {
		auto fireEffect = std::make_unique<FireEffect>(this);
		mActiveEffect = fireEffect.get();
		this->addChild(std::move(fireEffect));
	}
}
