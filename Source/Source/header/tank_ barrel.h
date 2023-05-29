#pragma once
#include "../../Library/gameutil.h"
#include "../header/Character.h"

class tank_barrel : public game_framework::CMovingBitmap {
public:
	tank_barrel(int _x, int _y);
	void init();
	void update(int x, int y);
	void draw();
	int GetAngele();
	void SetAngele(int);
private:
	time_t start = clock();
	int x, y;
	bool attacking;
	bool fire = false;
};