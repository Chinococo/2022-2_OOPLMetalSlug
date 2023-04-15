#pragma once
#include "Ground.h"
#include "Marco.h"
#include "Soldier.h"
#include <cstdlib>
#include <string>
#include <vector>
#include <ctime>
#include <set>

namespace game_framework {
	extern void createSoldierGroup();

	extern const int GRAVITY;
	extern int selectIndex;
	extern std::set<UINT> keydown;
	extern std::string state;
	extern Marco marco;
	extern std::vector<Soldier> soldiers;
	extern std::vector<Ground> grounds;
}
