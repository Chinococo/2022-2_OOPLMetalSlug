#pragma once
#include "../../Library/gameutil.h"
using namespace game_framework;
class MapObject:public CMovingBitmap
{
	public:
		MapObject(int _x, int _y, int _hp);
	protected:
		int hp;
};

