#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Soldier::Soldier(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {

}

void Soldier::init() {
	std::vector<std::string> paths;
	for (size_t i = 0; i < 1; i++) {
		paths.push_back("resources/img/enemy/soldier/idle/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/enemy/soldier/move/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/enemy/soldier/jump/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/enemy/soldier/lookUp/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/enemy/soldier/shoot/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/enemy/soldier/die/" + std::to_string(i) + ".bmp");
	}
	LoadBitmapByString(paths, RGB(153, 217, 234));
}

void Soldier::update() {
	if (alive) {
		control();
		move();
	}
}

void Soldier::control() { // AI
	/*
	int distanceX = marco.GetLeft() - x;
	if (distanceX > 0) {
		movingRight = true;
		movingLeft = false;
	}
	else if (distanceX < 0) {
		movingLeft = true;
		movingRight = false;
	}
	*/
	clock_t currentTime = clock();
	if (currentTime - lastJumpTime >= JUMP_COOLDOWN) {
		lastJumpTime = currentTime;
		jumping = true;
	}
	else {
		jumping = false;
	}
	/*
	if (currentTime - lastShootTime >= SHOOT_COOLDOWN) {
		lastShootTime = currentTime;
		shooting = true;
	}
	else {
		shooting = false;
	}
	*/
}

void Soldier::move() {
	dx = 0;
	dy = 0;
	collideWithBullet();
	collideWithWall();
	moveLeftRight();
	collideWithGround();
	jumpAndFall();
	shoot();
	x += dx;
	y += dy;
}

void Soldier::shoot() {
	if (shooting) {
		addBullet(x, y, 20, facingX, facingY, "enemy");
	}
}

void Soldier::moveLeftRight() {
	if (movingLeft) {
		dx += -speedX;
		facingX = -1;
	}
	if (movingRight) {
		dx += speedX;
		facingX = 1;
	}
}

void Soldier::jumpAndFall() {
	if (jumping && !inAir) {
		velocityY = -20;
		inAir = true;
	}
	else {
		velocityY += GRAVITY;
	}
	dy += velocityY;
}

void Soldier::collideWithBullet() {
	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i].owner == "hero" && IsOverlap(*this, bullets[i])) {
			alive = false;
		}
	}
}

void Soldier::collideWithGround() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			dy = Ground::GetX_Height(grounds[i], x) - GetHeight() - y;
			velocityY = 0;
			inAir = false;
		}
	}
}

void Soldier::collideWithWall() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (dx > 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			dx = 0;
		}
		else if (dx < 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			dx = 0;
		}
	}
}

void Soldier::die() {

}

void Soldier::draw() {
	if (alive) {
		SetTopLeft(x, y);
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

Soldier & Soldier::operator=(const Soldier & other)
{
	/*if (this == &other) {
		return *this;
	}
	return *this;*/
	this->lastJumpTime = other.lastJumpTime;
	this->lastShootTime = clock();
	int velocityY = other.velocityY;
	/*
	const int JUMP_COOLDOWN = 2000;
	const int SHOOT_COOLDOWN = 1000;
	bool movingLeft = false;
	bool movingRight = false;
	bool jumping = false;
	bool inAir = false;
	bool lookingUp = false;
	bool pressDown = false;
	bool shooting = false;
	*/
	return *this;
}

