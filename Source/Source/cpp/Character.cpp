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
	inAir = true;
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
	for (std::size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
  			dy = -1;
			velocityY = 0;
			inAir = false;
		}
		bool check = grounds[i].start.first == grounds[i].end.first;
		if (Ground::isOnGroundRight(*this, grounds[i]) == 1&& grounds[i].start.first== grounds[i].end.first ) {
			if(dx<0)
				dx = 0;
		}
		if (Ground::isOnGroundLeft(*this, grounds[i]) == 1 && grounds[i].start.first == grounds[i].end.first) {
			if (dx > 0)
				dx =0;
		}
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
	if(inAir)
		dy += velocityY;
	if ((lastdy[0] <= 0 && lastdy[1] >= 0))
		dy = 0;
	prevLeft = x;
	prevTop = y;
	x += dx;
	y += dy;
	lastdy.push_back(dy);
	if (lastdy.size() > 2)
		lastdy.erase(lastdy.begin());
}

void Character::draw() {
	SetTopLeft(x, y);
	ShowBitmap();
}
