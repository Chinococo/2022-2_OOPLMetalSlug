#pragma once
#include<chrono>
#include "../../Library/gameutil.h"

class Character : public game_framework::CMovingBitmap {
public:
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
	bool IsOverlap_(Character) ;
  
	bool isAlive() const;
	void dead();
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
	std::pair<std::pair<int, int>, std::pair<int, int>> CollideBox = { {-1,-1},{-1,-1} };
	clock_t start = clock();
};
