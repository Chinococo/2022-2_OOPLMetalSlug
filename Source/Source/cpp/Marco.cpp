#include "stdafx.h"
#include <chrono>
#include "../header/GameStorage.h"

using namespace game_framework;

Marco::Marco(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {

}

void Marco::init() {
	std::vector<std::string> paths;
	for (size_t i = 0; i < 4; i++) {
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
	LoadBitmapByString(paths, RGB(0, 0, 0));
	animationRanges.push_back({ 0, 4 });
	animationRange = animationRanges[static_cast<int>(action)];
}

void Marco::update() {
	if (alive) {
		control();
		move();
	}
	else {
		die();
	}
	changeAnimation();
	updateAnimation();
}

void Marco::control() {
	movingLeft = keyDowns.count(VK_LEFT);
	movingRight = keyDowns.count(VK_RIGHT);
	jumping = keyDowns.count(VK_SPACE);
	lookingUp = keyDowns.count(VK_UP);
	pressingDown = keyDowns.count(VK_DOWN);
	clock_t currentTime = clock();
	attacking = keyDowns.count(0x5A);
	if (attacking) {
		if (currentTime - lastAttackTime >= ATTACK_COOLDOWN) {
			lastAttackTime = currentTime;
		}else {
			attacking = false;
		}
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
	attack();
	x += dx;
	y += dy;
}

void Marco::attack() {
	if (attacking) {
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
		velocityY = JUMP_VELOCITY;
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

void Marco::changeAnimation() {
	if (action != lastAction) {
		animationRange = animationRanges[static_cast<int>(action)];
		SetFrameIndexOfBitmap(GetFrameIndexOfBitmap() + animationRange.first + ((flip) ? animationflipBias : 0));
	}
}

void Marco::updateAnimation() {
	if (clock() - start > ANIMATION_DELAY) {
		SetFrameIndexOfBitmap((GetFrameIndexOfBitmap() + 1) % (animationRange.second - animationRange.first));
		start = clock();
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
	animationRange = animationRanges[static_cast<int>(Action::DIE)];
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
