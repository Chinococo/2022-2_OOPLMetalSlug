#pragma once
#include "../header/Marco.h"
#include "../header/Soldier.h"
#include "../header/Ground.h"
#include "../header/Bullet.h"
#include "../header/MapObject.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>

namespace game_framework {
	// function
	extern std::vector<std::vector<std::string>> readCSV(const std::string& filename);
	extern void createSoldiers();
	extern void createGrounds();
	extern void createMap();
	extern void removeInactiveSolider();
	extern void addBullet(int x, int y, int speedX, int facingX, int facingY, std::string owner);
	extern void removeInactiveBullets();
	extern void removeMapObject();
	extern void updateCharacter();
	extern void updateUnderCharacterLayer();
	extern void updateUpperCharacterLayer();
	extern void updateMapObject();
	extern void createMapObject();
	// map
	extern std::string state;
	extern int selectIndex;
	extern CMovingBitmap background;
	extern CMovingBitmap background_mission1;
	extern CMovingBitmap arrow;
	extern std::vector<CMovingBitmap> mainmenuButtons;
	extern int ViewPointX;
	extern int ViewPointY;
	extern int ViewPointYInit;
	extern int MapScrollSpeed;
	extern std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> UnderCharacter;
	extern std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> UpperCharacter;

	// character
	extern const int GRAVITY;
	extern std::set<UINT> keyDowns;
	extern Marco marco;
	extern std::vector <MapObject> MapObjects;
	extern std::vector<Soldier> soldiers;
	extern std::vector<Bullet> bullets;
	extern std::vector<Ground> grounds;
	extern bool scroll;
	extern bool Loading;
}
