#pragma once
#include "../../Library/gameutil.h"
using namespace game_framework;
class MapObject:public CMovingBitmap
{
	public:
		MapObject(int _x, int _y, int _hp, vector<string> _path);
		void update();
		bool isAlive();
		void collideWithBullet();
		void init();
	protected:
		int hp;
		int now_hp;
		int x;
		int y;
		vector<string> path;
};

