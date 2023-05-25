#pragma once
#include "../../Library/gameutil.h"
#include <time.h>
class Boss1_fire : public game_framework::CMovingBitmap {
public:
	Boss1_fire(int x, int y);
	void init();
	void move();
	void draw();
	void setXY(int _x, int _y);
	bool isAlive = false;
private:
	time_t start;
	int x, y;
	int dy = -10;
};