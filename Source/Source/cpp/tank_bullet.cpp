#include "stdafx.h"
#include "../header/GameStorage.h"
tank_bullet::tank_bullet(int _x, int _y)
{
	this->start = clock();
	this->x = _x;
	this->y = _y;

}void tank_bullet::init() {
	this->LoadBitmapByString({ "resources/img_v2/boss1/canno/fire/0.bmp" }, RGB(255, 255, 255));
}
void tank_bullet::move()
{
	if (clock() - start > 100) {
		x -= 5;
		y += dy;
		if (dy < 4)
			dy += 1;
		start = clock();
	}
	this->SetTopLeft(ViewPointX + x, y - ViewPointYInit + ViewPointY);
	if (IsOverlap(*this, marco)) {
		this->isAlive = false;
		marco.dead();
	}
}

void tank_bullet::draw()
{
	this->ShowBitmap(3);
}
void tank_bullet::setXY(int _x, int _y) {
	this->x = _x;
	this->y = _y;
}
