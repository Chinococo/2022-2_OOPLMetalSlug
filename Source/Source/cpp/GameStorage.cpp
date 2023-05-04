#include "stdafx.h"
#include "../header/GameStorage.h"

namespace game_framework {
	void createSoldiers() {
		soldiers.push_back(Soldier(500, 500));
	}
	void removeInactiveBullets() {
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &bullet) {
			return !bullet.isAlive();
		}), bullets.end());
	}

	const int GRAVITY = 30;
	std::set<UINT> keyDowns;
	Marco marco(200, 500);
	std::vector<Soldier> soldiers;
	std::vector<Bullet> bullets;
}
