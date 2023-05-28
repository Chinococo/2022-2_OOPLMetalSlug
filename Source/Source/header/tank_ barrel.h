#pragma once
#include "../../Library/gameutil.h"
#include "../header/Character.h"
class tank_barrel : public game_framework::CMovingBitmap {
public:
	tank_barrel(int _x, int _y);
	void init();
	void update();
	void draw();
	int GetAngele();
	void SetAngele(int);
private:
	int angle = 0;
	time_t start_AI = clock();
	int x, y;
};