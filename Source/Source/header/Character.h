#pragma once
#include<chrono>
#include "../../Library/gameutil.h"

using ColBox = std::pair<std::pair<int, int>, std::pair<int, int>>;

enum class Direction {
	NONE, LEFT, RIGHT, UP, DOWN
};

class Character : public game_framework::CMovingBitmap {
public:
	int x;
	int y;
	ColBox CollideBox = { {-1, -1},{-1, -1} };
	Character(int _x, int _y, int _speedX);
	virtual void init() {}
	virtual void update() {}
	virtual void control() {}
	virtual void move() {}
	virtual void moveLeftRight() {}
	virtual void jumpAndFall() {}
	virtual void updateAction() {}
	virtual void changeAnimation() {}
	virtual void updateAnimation() {}
	virtual void collideWithGround() {}
	virtual void collideWithWall() {}
	virtual void draw() {}
	bool IsOverlap_(Character);
	bool isAlive() const;
	virtual void dead();
	bool myIsOverlap(Character *other);
	virtual ColBox getColBox(void);

protected:
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
