#include "stdafx.h"
#include "../header/GameStorage.h"
#include <cmath>
tank_bullet::tank_bullet(int _x, int _y)
{
	this->start = clock();
	this->angle = ((((tank_barrel_angle + 22) % 32) * (static_cast<float>(360) / 32)) / 180) * 3.14f;
	this->x = _x+50+ int(25 * cos(angle));
	this->y = _y+50+int(25 * sin(angle));
	


}void tank_bullet::init() {
	this->LoadBitmapByString({ "resources/img_v2/boss1/canno/fire/0.bmp" }, RGB(255, 255, 255));
}
void tank_bullet::move()
{
	if (clock() - start > 100) {
		x += int(25*cos(angle));
		y += int(25*sin(angle));
		start = clock();
	}
	this->SetTopLeft(ViewPointX + x, y - ViewPointYInit + ViewPointY);
	/*if (IsOverlap(*this, marco)) {
		this->isAlive = false;
		marco.dead();
	}*/
}

void tank_bullet::draw()
{
	this->ShowBitmap(3);
}
void tank_bullet::setXY(int _x, int _y) {
	this->x = _x;
	this->y = _y;
}
