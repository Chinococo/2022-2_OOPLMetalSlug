#pragma once
#include "../../Library/gameutil.h"

class Character : public game_framework::CMovingBitmap {
public:
	Character(int _x, int _y, int _speed, int _ammo);
	virtual ~Character() = default;
	virtual void init() = 0;
	virtual void update() = 0;
	void update_animation();
	void checkAlive();
	void move();
	void draw();
	int  prevTop;
	int  prevLeft;
	int x;
	int y;
	int speed;
	int ammo;
	int start_ammo;
	int flip = false; // It is difficult to flip the image in code, I keep this unused now.
	int direction = 1;
	bool movingLeft = false;
	bool movingRight = false;
	bool alive = true;
	int health = 1;
	int velocityY = 0;
	bool jumping = false;
	bool inAir = false;
	int action = 0;
};
