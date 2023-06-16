#include "stdafx.h"
#include "../header/GameStorage.h"
Enemy_tank_bullet::Enemy_tank_bullet(int _x, int _y, std::string direction)
{
	this->start = clock();
	this->x = _x;
	this->y = _y;
	this->direction = direction;
	init();

}void   Enemy_tank_bullet::init() {
	if (direction == "left")
		this->LoadBitmapByString({ "resources/enemy_tank/enemy_bullet.bmp" }, RGB(255, 255, 255));
	else
		this->LoadBitmapByString({ "resources/enemy_tank/flip_enemy_bullet.bmp" }, RGB(255, 255, 255));
	
}
void  Enemy_tank_bullet::move()
{
	if (clock() - start > 100) {
		if (direction == "left")
			x -= 10;
		else
			x += 10;
		start = clock();
	}
	this->SetTopLeft(x, y - ViewPointYInit + ViewPointY);
	if (IsOverlap(*this, marco)) {
		this->alive = false;
		marco.dead();
	}
}

void  Enemy_tank_bullet::draw()
{
	this->ShowBitmap();
}
void  Enemy_tank_bullet::setXY(int _x, int _y) {
	this->x = _x;
	this->y = _y;
}

bool Enemy_tank_bullet::isAlive()
{
	return alive;
}

void Enemy_tank_bullet::dead()
{
	alive = false;
}
