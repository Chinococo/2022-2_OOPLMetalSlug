#include "stdafx.h"
#include "../header/GameStorage.h"
#include <cmath>
tank_bullet::tank_bullet(int _x, int _y):Character(x,y,0)
{
	this->start = clock();
	this->angle = ((((tank_barrel_angle + 22) % 32) * (static_cast<float>(360) / 32)) / 180) * 3.14f;
	/*
	this->x = _x+30+ int(25 * cos(angle));
	this->y = _y+60+int(25 * sin(angle));
	*/
	this->x = _x + 30 + int(50 * cos(angle));
	this->y = _y + 60 + int(50 * sin(angle));
	


}void tank_bullet::init() {
	this->LoadBitmapByString({ "resources/img_v2/boss1/canno/fire/0.bmp" }, RGB(255, 255, 255));
}
void tank_bullet::move()
{
	if (clock() - start > 100) {
		x += int(50 * cos(angle));
		y += int(50 * sin(angle));
		/*
		x += int(25*cos(angle));
		y += int(25*sin(angle));
		*/
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

}
void tank_bullet::dead() {
	alive = false;
}

bool tank_bullet::isOverlap_tank_bullet(Character other)
{
	const int relPosLeft = x;
	const int relPosTop = y;
	const int relPosRight = x + GetWidth();
	const int relPosBottom = y + GetHeight();
	const int otherRelPosLeft = other.x + ViewPointX;
	const int otherRelPosTop = other.y - ViewPointY + ViewPointYInit;
	const int otherRelPosRight = otherRelPosLeft + other.GetWidth();
	const int otherRelPosBottom = otherRelPosTop + other.GetHeight();
	if (relPosLeft < other.CollideBox.second.first &&
		relPosRight > other.CollideBox.first.first &&
		relPosTop < other.CollideBox.second.second &&
		relPosBottom > other.CollideBox.first.second) {
		return true;
	}
	return false;
}
