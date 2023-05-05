#include "stdafx.h"
#include <chrono>
#include "../header/GameStorage.h"

using namespace game_framework;

Marco::Marco(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {

}

void Marco::init() {
	std::vector<std::string> paths;
	for (size_t i = 0; i < 10; i++) {
		paths.push_back("resources/image/HeroMarco/idle/" + std::to_string(i) + ".bmp");
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
	LoadBitmapByString(paths, RGB(0,0,0));
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
	moveLeftRight();
	collideWithWall();
	collideWithGround();
	jumpAndFall();
	shoot();
	update_animation();
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

void Marco::update_animation() {
	this->animation_range = { 0,9 };

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);

	if (duration > std::chrono::milliseconds(100)) {
		this->SetFrameIndexOfBitmap(((this->GetFrameIndexOfBitmap() + 1) % (this->animation_range.second - this->animation_range.first)) + this->animation_range.first);
		start = std::chrono::high_resolution_clock::now();
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
		bool t = Ground::isOnGroundLeft(*this, grounds[i]);
		if (t) {
			dx = dx;
		}
		if (dx >= 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			dx = 0;
		}
		else if (dx <= 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
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
