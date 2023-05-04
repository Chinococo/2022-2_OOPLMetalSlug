#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Marco::Marco(int _x, int _y) : Character(_x, _y) {

}

void Marco::init() {
	std::vector<std::string> paths;
	for (size_t i = 0; i < 4; i++) {
		paths.push_back("resources/hero/marco/idle/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/hero/marco/move/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/hero/marco/jump/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/hero/marco/lookUp/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/hero/marco/shoot/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/hero/marco/die/" + std::to_string(i) + ".bmp");
	}
	LoadBitmapByString(paths, RGB(153, 217, 234));
}

void Marco::update() {
	if (alive) {
		control();
		move();
	}
}

void Marco::control() {
	movingLeft = keyDowns.count(VK_LEFT);
	movingRight = keyDowns.count(VK_RIGHT);
	jumping = keyDowns.count(VK_SPACE);
	lookingUp = keyDowns.count(VK_UP);
	pressDown = keyDowns.count(VK_DOWN);
	shooting = keyDowns.count(0x5A); // Z
}

void Marco::move() {
	dx = 0;
	dy = 0;
	moveLeftRight();
	jumpAndFall();
	collideWithBullet();
	collideWithGround();
	collideWithWall();
	x += dx;
	y += dy;
}

void Marco::moveLeftRight() {
	if (movingLeft) {
		dx += -speedX;
		facingX = -1;
	}
	if (movingRight) {
		dx += speedX;
		facingX = 1;
	}
}

void Marco::jumpAndFall() {
	if (jumping && !inAir) {
		velocityY = -30;
		inAir = true;
	}
	else {
		velocityY += GRAVITY;
	}
	dy += velocityY;
}

void Marco::collideWithBullet() {

}

void Marco::collideWithGround() {
	
}

void Marco::collideWithWall() {

}

void Marco::draw() {
	if (alive) {
		SetTopLeft(x, y);
		ShowBitmap();
	}
}
