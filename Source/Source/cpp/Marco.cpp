#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Marco::Marco(int _x, int _y, int _speed, int _ammo) : Character(_x, _y, _speed, _ammo) {

}

void Marco::init() {
	std::vector<std::string> paths;
	for (int i = 0; i < 11; i++) {
		std::string path = "resources/image/HeroMarco/Idle/" + std::to_string(i) + ".bmp";
		paths.push_back(path);
	}
	LoadBitmapByString(paths, RGB(255, 255, 255));
	SetAnimation(100, false);
}

void Marco::update() {
	this->dx = 0;
	control();
	move();
	draw();
}

void Marco::control() {
	movingLeft = game_framework::keydown.count(VK_LEFT);
	movingRight = game_framework::keydown.count(VK_RIGHT);
	jumping = game_framework::keydown.count(VK_SPACE);
}
