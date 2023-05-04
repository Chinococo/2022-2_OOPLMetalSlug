#pragma once
#include "../../Library/gameutil.h"

class Character : public game_framework::CMovingBitmap {
public:
	Character(int _x, int _y, int _speedX);
	virtual void init() = 0;
	virtual void update() = 0;
	virtual void control() = 0;
	virtual void move() = 0;
	virtual void moveLeftRight() = 0;
	virtual void jumpAndFall() = 0;
	virtual void collideWithGround() = 0;
	virtual void collideWithWall() = 0;
	virtual void die() = 0;
	virtual void draw() = 0;
protected:
	int x;
	int y;
	int dx = 0;
	int dy = 0;
	int speedX;
	int facingX = 1;
	int facingY = 0;
	bool alive = true;
	bool dying = false;
};
