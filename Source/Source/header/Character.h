#pragma once
#include "../../Library/gameutil.h"
#include <vector>
#include <chrono>
class Character : public game_framework::CMovingBitmap {
public:
	Character(int _x, int _y, int _speed, int _ammo);
	virtual ~Character() = default;
	virtual void init() = 0;
	virtual void update() = 0;
	void update_animation();
	void checkAlive();
	void move();
	void ShowBitmapBySetting();
	void gravity();
	void keybroid_control();
	void ground_evnet();
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
	bool movingUp = false;
	bool alive = true;
	int health = 1;
	int velocityY = 0;
	bool jumping = false;
	std::pair<int, int> animation_range = { 0,9 };
	int dx = 0;
	int dy = 0;
	bool inAir = false;
	int action = 0;
	std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();
	std::vector<int> lastdy = {-1,-11};
};