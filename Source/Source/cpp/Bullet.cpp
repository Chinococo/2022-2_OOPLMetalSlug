#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Bullet::Bullet(int _x, int _y, int _facingX, std::string _owner) : Character(_x, _y) {
	facingX = _facingX;
	owner = _owner;
}

void Bullet::init() {
	std::vector<std::string> paths;
	for (size_t i = 0; i < 4; i++) {
		paths.push_back("resources/item/bullet/move/" + std::to_string(i) + ".bmp");
	}
	LoadBitmapByString(paths, RGB(153, 217, 234));
}

void Bullet::update() {
	if (alive) {
		move();
	}
}

void Bullet::control() {

}

void Bullet::move() {
	dx = 0;
	dy = 0;
	moveLeftRight();
	x += dx;
	y += dy;
}

void Bullet::moveLeftRight() {
	if (facingX == -1) {
		dx += -speedX;
	}
	if (facingX == 1) {
		dx += speedX;
	}
}

void Bullet::jumpAndFall() {

}

void Bullet::collideWithBullet() {
	
}

void Bullet::collideWithGround() {
	alive = false;
}

void Bullet::collideWithWall() {
	alive = false;
}

void Bullet::draw() {
	if (alive) {
		SetTopLeft(x, y);
		ShowBitmap();
	}
}

bool Bullet::isAlive() const {
	return alive;
}
