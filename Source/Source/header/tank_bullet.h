#pragma once
#include "../../Library/gameutil.h"
#include <time.h>
class tank_bullet : public Character {
public:
	void init();
	tank_bullet(int _x, int _y);
	void move();
	void draw();
	void setXY(int _x, int _y);
	void collideWithCharacter();
	void dead();
private:
	time_t start;
	int x, y;
	int dy = -10;
	float angle;
};