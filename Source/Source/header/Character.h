#pragma once
#include<chrono>
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
	virtual void updateAction() = 0;
	virtual void changeAnimation() = 0;
	virtual void updateAnimation() = 0;
	virtual void collideWithGround() = 0;
	virtual void collideWithWall() = 0;
	virtual void draw() = 0;
	bool isAlive() const;
	bool myIsOverlap(Character *other);
protected:
	int x;
	int y;
	int dx = 0;
	int dy = 0;
	int speedX;
	int facingX = 1;
	int facingY = 0;
	int animationflipBias = 0;
	int animationDelay;
	bool alive = true;
	bool dying = false;
	bool flip = false;
	clock_t deathTimer = clock();
	std::pair<int, int> animationRange; // { start, end }, including start, excluding end
	std::vector<std::pair<int, int>> animationRanges;
	std::vector<int> animationDelays;
	clock_t start = clock();
};
