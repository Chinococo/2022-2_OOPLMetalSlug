#pragma once
#include "Character.h"

class Marco : public Character {
public:
	Marco(int _x, int _y, int _speed, int _ammo);
	virtual void init() override;
	virtual void update() override;
	void control();
};
