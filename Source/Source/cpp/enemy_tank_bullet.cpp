#include "stdafx.h"
#include "../header/GameStorage.h"
Enemy_tank_bullet::Enemy_tank_bullet(int _x, int _y)
{
	this->start = clock();
	this->x = _x;
	this->y = _y;

}void   Enemy_tank_bullet::init() {
	this->LoadBitmapByString({ "resources/img_v2/boss1/canno/laser/air0.bmp" }, RGB(255, 255, 255));
}
void  Enemy_tank_bullet::move()
{
	if (clock() - start > 100) {
		x -= 10;
		start = clock();
	}
	this->SetTopLeft(ViewPointX + x, y - ViewPointYInit + ViewPointY);
	if (IsOverlap(*this, marco)) {
		this->isAlive = false;
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
