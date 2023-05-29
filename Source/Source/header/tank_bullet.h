#pragma once
#include "../../Library/gameutil.h"
#include <time.h>
class tank_bullet : public game_framework::CMovingBitmap {
public:
	void init();
	tank_bullet(int _x, int _y);
	void move();
	void draw();
	void setXY(int _x, int _y);
	bool isAlive = false;
private:
	time_t start;
	int x, y;
	int dy = -10;
	float angle;
};