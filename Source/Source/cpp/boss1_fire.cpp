#include "stdafx.h"
#include "../header/GameStorage.h"
Boss1_fire::Boss1_fire(int _x, int _y)
{
	this->start = clock();
	this->x = _x;
	this->y = _y;

}void Boss1_fire::init() {
	this->LoadBitmapByString({ "resources/img_v2/boss1/canno/fire/0.bmp" }, RGB(255, 255, 255));
}
void Boss1_fire::move()
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

void Boss1_fire::draw()
{
	this->ShowBitmap(3);
}
void Boss1_fire::setXY(int _x, int _y) {
	this->x = _x;
	this->y = _y;
}
