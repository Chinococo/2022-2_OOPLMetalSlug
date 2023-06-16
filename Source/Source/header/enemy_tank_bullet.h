#pragma once
#include "../../Library/gameutil.h"
#include <time.h>
class Enemy_tank_bullet : public game_framework::CMovingBitmap {
public:
	Enemy_tank_bullet(int x, int y,string);
	void init();
	void move();
	void draw();
	void setXY(int _x, int _y);
	bool alive = true;
	bool isAlive();
	void dead();
private:
	time_t start;
	int x, y;
	std::string direction;
};