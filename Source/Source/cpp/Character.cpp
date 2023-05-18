#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Character::Character(int _x, int _y, int _speedX) : x(_x), y(_y), speedX(_speedX) {

}

bool Character::isAlive() const {
	return alive;
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
