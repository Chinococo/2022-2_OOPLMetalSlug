#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Character::Character(int _x, int _y, int _speedX) : x(_x), y(_y), speedX(_speedX) {

}

bool Character::IsOverlap_(Character bmp)
{
	if (bmp.CollideBox.first.first == -1 && bmp.CollideBox.first.second == -1)
		return IsOverlap(*this, bmp);
	bool check = x < bmp.CollideBox.second.first;
	bool check2 = x + GetWidth() > bmp.CollideBox.first.first;
	bool check3 = y < bmp.CollideBox.second.second;
	bool check4 = y + GetHeight() > bmp.CollideBox.first.second;
	if (x+abs(ViewPointX) < bmp.CollideBox.second.first &&
		x+ abs(ViewPointX) + GetWidth() > bmp.CollideBox.first.first &&
		y-ViewPointY+ViewPointYInit < bmp.CollideBox.second.second &&
		y - ViewPointY + ViewPointYInit + GetHeight() > bmp.CollideBox.first.second) {
		return true;
	}
	else {
		return false;
	}
}



bool Character::isAlive()const {
	return alive;
}
void  Character::dead() {
	alive=false;
}
bool Character::myIsOverlap(Character *other) {
	int top = GetTop();
	int left = GetLeft();
	int bottom = GetTop() + GetHeight();
	int right = GetLeft() + GetWidth();

	int otherTop = other->GetTop();
	int otherLeft = other->GetLeft();
	int otherBottom = other->GetTop() + other->GetHeight();
	int otherRight = other->GetLeft() + other->GetWidth();

	if (dynamic_cast<Marco *>(other)) {
		otherTop += ViewPointY;
		otherLeft += ViewPointX;
		otherBottom += ViewPointY;
		otherRight += ViewPointX;
	}

	if (bottom < otherTop || otherBottom < top) {
		return false;
	}
	if (right < otherLeft || otherRight < left) {
		return false;
	}
	return true;
}


ColBox Character::getColBox(void) {
	return CollideBox;
}
