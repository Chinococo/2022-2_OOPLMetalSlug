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
	
	inAir = true;
	for (std::size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			int t1 = Ground::GetX_Height(grounds[i], this->x);
			int t2 = this->y;
			int t3 = this->GetHeight();
			auto t = grounds[i];
			dy = Ground::GetX_Height(grounds[i], this->x) - this->GetHeight() - this->y;
			velocityY = 0;
			inAir = false;
		}
	}
	keybroid_control();
	gravity();
	for (std::size_t i = 0; i < grounds.size(); i++) {
		bool check = grounds[i].start.first == grounds[i].end.first;
		if (Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			if (dx < 0)
				dx = 0;
		}
		if (Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			if (dx > 0)
				dx = 0;
		}
	}
	prevLeft = x;
	prevTop = y;
	x += dx;
	y += dy;

}

void Character::gravity()
{
	velocityY += GRAVITY;
	// max falling velocity, can turn of or off
	if (velocityY > 15) {
		velocityY = 15;
	}
	if (inAir)
		dy += velocityY;
}

void Character::keybroid_control()
{
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
}

void Character::ground_evnet()
{
	inAir = true;
	for (std::size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1 ) {
			int t1 = Ground::GetX_Height(grounds[i],this->x);
			int t2 = this->y;
			int t3 = this->GetHeight();
			auto t = grounds[i];
			dy = Ground::GetX_Height(grounds[i],this->x) - this->GetHeight() - this->y;
			velocityY = 0;
			inAir = false;
		}
		bool check = grounds[i].start.first == grounds[i].end.first;
		if (Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			if (dx < 0)
				dx = 0;
		}
		if (Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			if (dx > 0)
				dx = 0;
		}
	}
}

void Character::draw() {
	SetTopLeft(x, y);
	ShowBitmap();
}
