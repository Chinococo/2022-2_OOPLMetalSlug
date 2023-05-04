#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Marco::Marco(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {

}

void Marco::init() {
	std::vector<std::string> paths;
	for (size_t i = 0; i < 1; i++) {
		paths.push_back("resources/img/hero/marco/idle/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/hero/marco/move/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/hero/marco/jump/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/hero/marco/lookUp/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/hero/marco/shoot/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/img/hero/marco/die/" + std::to_string(i) + ".bmp");
	}
	LoadBitmapByString(paths, RGB(153, 217, 234));
}

void Marco::update() {
	if (alive) {
		control();
		move();
	}
	else {
		die();
	}
}

void Marco::control() {
	movingLeft = keyDowns.count(VK_LEFT);
	movingRight = keyDowns.count(VK_RIGHT);
	jumping = keyDowns.count(VK_SPACE);
	lookingUp = keyDowns.count(VK_UP);
	pressDown = keyDowns.count(VK_DOWN);
	clock_t currentTime = clock();
	if (currentTime - lastShootTime >= SHOOT_COOLDOWN) {
		shooting = keyDowns.count(0x5A);
		if (shooting) {
			lastShootTime = currentTime;
		}
	}
	else {
		shooting = false;
	}
}

void Marco::move() {
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

void Marco::shoot() {
	if (shooting) {
		addBullet(x, y, 20, facingX, facingY, "hero");
	}
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
		velocityY = -20;
		inAir = true;
	}
	else {
		velocityY += GRAVITY;
	}
	dy += velocityY;
}

void Marco::collideWithBullet() {
	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i].owner == "enemy" && IsOverlap(*this, bullets[i])) {
			alive = false;
		}
	}
}

void Marco::collideWithGround() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			dy = Ground::GetX_Height(grounds[i], x) - GetHeight() - y;
			velocityY = 0;
			inAir = false;
		}
	}
}

void Marco::collideWithWall() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (dx > 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			dx = 0;
		}
		else if (dx < 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			dx = 0;
		}
	}
}

void Marco::die() {

}

void Marco::draw() {
	if (alive) {
		SetTopLeft(x, y);
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}
