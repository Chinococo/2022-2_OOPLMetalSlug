#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Soldier::Soldier(int _x, int _y) : Character(_x, _y) {

}

void Soldier::init() {
	std::vector<std::string> paths;
	for (size_t i = 0; i < 4; i++) {
		paths.push_back("resources/enemy/soldier/idle/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/enemy/soldier/move/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/enemy/soldier/jump/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/enemy/soldier/lookUp/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/enemy/soldier/shoot/" + std::to_string(i) + ".bmp");
	}
	for (size_t i = 0; i < 0; i++) {
		paths.push_back("resources/enemy/soldier/die/" + std::to_string(i) + ".bmp");
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

}

void Soldier::move() {
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

void Soldier::moveLeftRight() {

}

void Soldier::jumpAndFall() {

}

void Soldier::collideWithBullet() {

}

void Soldier::collideWithGround() {

}

void Soldier::collideWithWall() {

}

void Soldier::draw() {
	if (alive) {
		SetTopLeft(x, y);
		ShowBitmap();
	}
}
