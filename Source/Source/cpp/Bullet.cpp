#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Bullet::Bullet(int _x, int _y, int _speedX, int _facingX, int _facingY, std::string _owner) : Character(_x, _y, _speedX) {
	facingX = _facingX;
	facingY = _facingY;
	owner = _owner;
}

void Bullet::init() {
	std::vector<std::string> paths;
	for (size_t i = 0; i < 1; i++) {
		paths.push_back("resources/img/item/bullet/move/" + std::to_string(i) + ".bmp");
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
	collideWithCharacter();
	collideWithWall();
	moveLeftRight();
	collideWithGround();
	jumpAndFall();
	x += dx;
	y += dy;
}

void Bullet::moveLeftRight() {
	if (facingX == -1) {
		dx += -speedX;
	}
	else if (facingX == 1) {
		dx += speedX;
	}
}

void Bullet::jumpAndFall() {
	if (facingY == -1) {
		dx = 0;
		dy += -speedX;
	}
	else if (facingY == 1) {
		dx = 0;
		dy += speedX;
	}
}

void Bullet::collideWithCharacter() {
	if (owner == "hero") {
		for (size_t i = 0; i < soldiers.size(); i++) {
			if (IsOverlap(*this, soldiers[i])) {
				alive = false;
			}
		}
	}
	else if (owner == "enemy") {
		if (IsOverlap(*this, marco)) {
			alive = false;
		}
	}
}

void Bullet::changeAnimation() {

}

void Bullet::updateAnimation() {

}

void Bullet::collideWithGround() {
	//alive = false;
}

void Bullet::collideWithWall() {
	//alive = false;
}

void Bullet::die() {
	
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
