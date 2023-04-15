#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

namespace game_framework {
	void createSoldierGroup() {
		soldiers.push_back(Soldier(600, 300, 1, 999));
	}

	const int GRAVITY = 1;
	int selectIndex = 0;
	std::set<UINT> keydown;
	std::string state = "init";
	Marco marco(300, 300, 10, 999);
	std::vector<Soldier> soldiers;
	std::vector <Ground> grounds;
}
