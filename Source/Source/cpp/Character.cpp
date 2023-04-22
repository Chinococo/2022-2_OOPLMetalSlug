#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Character::Character(int _x, int _y, int _speed, int _ammo) {
	x = _x;
	y = _y;
	speed = _speed;
	ammo = _ammo;
	start_ammo = _ammo;
}

void Character::update_animation() {

}

void Character::checkAlive() {
	if (health <= 0) {
		health = 0;
		speed = 0;
		alive = false;
	}
}

void Character::move() {
	int dx = 0;
	int dy = 0;
	if (movingLeft) {
		dx = -speed;
		flip = true;
		direction = -1;
	}
	if (movingRight) {
		dx = speed;
		flip = false;
		direction = 1;
	}
	if (jumping && !inAir) {
		velocityY = -15;
		jumping = false;
		inAir = true;
	}
	velocityY += GRAVITY;
	// max falling velocity, can turn of or off
	if (velocityY > 15) {
		velocityY = 15;
	}
	dy += velocityY;
	// no obstacle class is defined yet, so here we set a temporary ground for y axis.
	for (std::size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			dy = grounds[i].start.second - (y + GetHeight());
			velocityY = 0;
			inAir = false;
		}
	}
	x += dx;
	y += dy;
}

void Character::draw() {
	SetTopLeft(x, y);
	ShowBitmap();
}
