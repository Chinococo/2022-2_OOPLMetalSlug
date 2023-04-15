#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Soldier::Soldier(int _x, int _y, int _speed, int _ammo) : Character(_x, _y, _speed, _ammo) {
	jumpCooldown = JUMP_COOLDOWN;
}

void Soldier::init() {
	LoadBitmap({ "resources/testImage/giraffe.bmp" }, RGB(255, 255, 255));
}

void Soldier::update() {
	ai();
	move();
	draw();
}

void Soldier::ai() {
	movingLeft = false;
	movingRight = false;
	jumping = false;
	int distanceToMarcoX = x - marco.x;
	if (distanceToMarcoX > FIRE_RANGE) {
		movingLeft = true;
	}
	if (distanceToMarcoX < -FIRE_RANGE) {
		movingRight = true;
	}
	jumpCooldown--;
	if (jumpCooldown == 0) {
		jumping = true;
		jumpCooldown = JUMP_COOLDOWN;
	}
}
