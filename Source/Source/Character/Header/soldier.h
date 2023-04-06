#pragma once
#include "enemy.h"

class CSoldier : public CEnemy {
public:
	CSoldier();
	virtual ~CSoldier();
	int x;
	int y;
	int dx;
	int dy;
	clock_t jumpUpTime;
	bool isOnGround;
};
