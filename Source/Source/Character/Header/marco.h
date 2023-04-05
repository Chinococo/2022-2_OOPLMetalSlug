#pragma once
#include "hero.h"

class CMarco : public CHero {
public:
	CMarco();
	~CMarco();
	int x;
	int y;
	int dx;
	int dy;
	clock_t jumpUpTime;
	bool isOnGround;
};
