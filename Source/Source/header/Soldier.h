#pragma once
#include "Character.h"

class Soldier : public Character {
public:
	Soldier(int _x, int _y, int _speed, int _ammo);
	virtual void init() override;
	virtual void update() override;
	void ai();

	const int FIRE_RANGE = 30;
	const int JUMP_COOLDOWN = 100;
	int jumpCooldown;
};
