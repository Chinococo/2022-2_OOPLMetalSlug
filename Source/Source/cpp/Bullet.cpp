#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Bullet::Bullet(int _x, int _y, int _speedX, int _facingX, int _facingY, std::string _owner) : Character(_x, _y, _speedX) {
	owner = _owner;
	if (_facingY == -1) {
		movingUp = true;
	}
	else if (_facingY == 1) {
		movingDown = true;
	}
	else if (_facingX == -1) {
		movingLeft = true;
	}
	else {
		movingRight = true;
	}
}

void Bullet::init() {
	/*
	std::vector<std::string> paths;
	
	// right
	int delay = 300;
	std::pair<int, int> range = { 0, 1 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/bullet/HGBullet/moveHorizontal/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	// up
	delay = 300;
	range = { 1, 2 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/bullet/HGBullet/moveVertical/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);
	animationflipBias = range.second;



	// flip

	// left
	range = { 0, 1 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/bullet/HGBullet/moveHorizontal/flip_" + std::to_string(i) + ".bmp");
	}
	// down
	range = { 1, 2 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/bullet/HGBullet/moveVertical/flip_" + std::to_string(i) + ".bmp");
	}

	LoadBitmapByString(paths, RGB(0, 0, 0));
	animationRange = animationRanges[static_cast<int>(action)];
	animationDelay = animationDelays[static_cast<int>(action)];
	*/
	
	if (movingLeft) {
		LoadBitmapByString({ "resources/img_v2/bullet/HGBullet/moveHorizontal/flip_0.bmp" }, RGB(0, 0, 0));
	}
	else if (movingRight) {
		LoadBitmapByString({ "resources/img_v2/bullet/HGBullet/moveHorizontal/0.bmp" }, RGB(0, 0, 0));
	}
	else if (movingUp) {
		LoadBitmapByString({ "resources/img_v2/bullet/HGBullet/moveVertical/0.bmp" }, RGB(0, 0, 0));
	}
	else {
		LoadBitmapByString({ "resources/img_v2/bullet/HGBullet/moveVertical/flip_0.bmp" }, RGB(0, 0, 0));
	}
}

void Bullet::update() {
	if (alive) {
		control();
		move();
		/*
		updateAction();
		changeAnimation();
		updateAnimation();
		*/
	}
	else {
		action = Action::DIE;
		/*
		changeAnimation();
		updateAnimation();
		
		if (clock() - deathTimer > 100) {
			alive = false;
		}
		*/
	}
}

void Bullet::control() {
	if (clock() - aliveTimer > 1000) {
		alive = false;
	}
}

void Bullet::move() {
	dx = 0;
	dy = 0;
	collideWithCharacter();
	collideWithWall();
	moveLeftRight();
	collideWithGround();
	jumpAndFall();
	x += dx;
	y += dy;
}

void Bullet::moveLeftRight() {
	if (movingLeft) {
		dy = 0;
		dx += -speedX;
		facingX = -1;
		flip = true;
	}
	else if (movingRight) {
		dy = 0;
		dx += speedX;
		facingX = 1;
		flip = false;
	}
}

void Bullet::jumpAndFall() {
	if (movingUp) {
		dx = 0;
		dy += -speedX;
		facingX = -1;
		flip = true;
	}
	else if (movingDown) {
		dx = 0;
		dy += speedX;
		facingX = 1;
		flip = false;
	}
}

void Bullet::collideWithCharacter() {
	if (owner == "hero") {
		for (size_t i = 0; i < soldiers.size(); i++) {
			if (IsOverlap(*this, soldiers[i])) {
				alive = false;
			}
		}
		for (size_t i = 0; i < MapObjects.size(); i++) 
			if (IsOverlap(*this, MapObjects[i])&&MapObjects[i].isAlive()) {
				alive = false;
			}
	}
	else if (owner == "enemy") {
		if (IsOverlap(*this, marco)) {
			alive = false;
		}
	}
}

void Bullet::updateAction() {
	lastAction = action;
	if (movingLeft || movingRight) {
		action = Action::MOVE_H;
	}
	else if (movingUp || movingDown) {
		action = Action::MOVE_V;
	}
}

void Bullet::changeAnimation() {
	if (action != lastAction) {
		animationRange = animationRanges[static_cast<int>(action)];
		animationDelay = animationDelays[static_cast<int>(action)];
		SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
	}
}

void Bullet::updateAnimation() {
	if (clock() - start > animationDelay) {
		SetFrameIndexOfBitmap(((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first)) + animationRange.first + ((flip) ? animationflipBias : 0));
		start = clock();
	}
}

void Bullet::collideWithGround() {
	//alive = false;
}

void Bullet::collideWithWall() {
	//alive = false;
}

void Bullet::draw() {
	if (alive) {
		SetTopLeft(x, y);
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

Bullet &Bullet::operator=(const Bullet &other) {
	x = other.x;
	y = other.y;
	speedX = other.speedX;
	facingX = other.facingX;
	facingY = other.facingY;
	owner = other.owner;
	return *this;
}
