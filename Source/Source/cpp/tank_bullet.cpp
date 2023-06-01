#include "stdafx.h"
#include "../header/GameStorage.h"
#include <cmath>
tank_bullet::tank_bullet(int _x, int _y):Character(x,y,0)
{
	this->start = clock();
	this->angle = ((((tank_barrel_angle + 22) % 32) * (static_cast<float>(360) / 32)) / 180) * 3.14f;
	this->x = _x+30+ int(25 * cos(angle));
	this->y = _y+30+int(25 * sin(angle));
	


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
	this->ShowBitmap(1);
}
void tank_bullet::setXY(int _x, int _y) {
	this->x = _x;
	this->y = _y;
}

void tank_bullet::collideWithCharacter()
{
	for (size_t i = 0; i < soldiers.size(); i++) {
		if (IsOverlap(*this, soldiers[i])) {
			soldiers[i].dead();
			//alive = false;
			break;
		}
	}
	for (size_t i = 0; i < MapObjects.size(); i++)
		if (IsOverlap_(MapObjects[i]) && MapObjects[i].isAlive()) {
			//alive = false;
			break;
		}
	if (IsOverlap_(boss)){
		alive = false;
	}
}
void tank_bullet::dead() {
	alive = false;
}