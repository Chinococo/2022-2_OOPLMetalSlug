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
	for (int i = 0; i < 8; i++) {
		std::string path = "resources/image/HeroMarco/Up/" + std::to_string(i) + ".bmp";
		paths.push_back(path);
	}
	LoadBitmapByString(paths, RGB(0,0,0));
	//SetAnimation(100, false);
}

void Marco::update() {
	this->dx = 0;
	control();
	move();
	update_animation();
	draw();
}
void Marco::update_animation() {

	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start);

	if (duration > std::chrono::milliseconds(100)) {
		this->SetFrameIndexOfBitmap(((this->GetFrameIndexOfBitmap() + 1) % (this->animation_range.second-this->animation_range.first))+ this->animation_range.first);
		start = std::chrono::high_resolution_clock::now();
	}

}
void Marco::control() {
	movingLeft = game_framework::keydown.count(VK_LEFT);
	movingRight = game_framework::keydown.count(VK_RIGHT);
	jumping = game_framework::keydown.count(VK_SPACE);
	movingUp = game_framework::keydown.count(VK_UP);
	//shooting = game_framework::keydown.count(VK_UP);
}
