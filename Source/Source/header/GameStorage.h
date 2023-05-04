#pragma once
#include "../header/Marco.h"
#include "../header/Soldier.h"
#include "../header/Ground.h"
#include "../header/Bullet.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>

namespace game_framework {
	// function
	extern void createSoldiers();
	extern void createGrounds();
	extern void createMap();
	extern void removeInactiveBullets();

	// map
	extern std::string state;
	extern int selectIndex;
	extern CMovingBitmap background;
	extern CMovingBitmap arrow;
	extern std::vector<CMovingBitmap> mainmenuButtons;
	extern int ViewPointX;
	extern int ViewPointY;
	extern int MapScrollSpeed;
	extern std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> map;

	// character
	extern const int GRAVITY;
	extern std::set<UINT> keyDowns;
	extern Marco marco;
	extern std::vector<Soldier> soldiers;
	extern std::vector<Bullet> bullets;
	extern std::vector<Ground> grounds;
}
