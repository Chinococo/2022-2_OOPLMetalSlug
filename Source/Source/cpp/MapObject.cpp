#include "stdafx.h"
#include "../header/GameStorage.h"
using namespace game_framework;
MapObject::MapObject(int _x, int _y, int _hp) {
	this->SetTopLeft(_x, _y);
	this->hp = _hp;

}

