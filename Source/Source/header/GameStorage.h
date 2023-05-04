#pragma once
#include "../header/Marco.h"
#include "../header/Soldier.h"
#include "../header/Ground.h"
#include "../header/Bullet.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>

namespace game_framework {
	extern void createSoldiers();
	extern void removeInactiveBullets();

	extern const int GRAVITY;
	extern std::set<UINT> keyDowns;
	extern Marco marco;
	extern std::vector<Soldier> soldiers;
	extern std::vector<Bullet> bullets;
}
