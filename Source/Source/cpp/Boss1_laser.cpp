#include "stdafx.h"
#include "../header/GameStorage.h"
Boss1_laser::Boss1_laser(int _x, int _y)
{
	this->start = clock();
	this->x = _x;
	this->y = _y;
	
}void  Boss1_laser::init() {
	this->LoadBitmapByString({ "resources/img_v2/boss1/canno/laser/air0.bmp" },RGB(255,255,255));
}
void Boss1_laser::move()
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

void Boss1_laser::draw()
{
	this->ShowBitmap();
}
void Boss1_laser::setXY(int _x, int _y) {
	this->x = _x;
	this->y = _y;
}
