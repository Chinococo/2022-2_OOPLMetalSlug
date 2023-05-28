#pragma once
#include "../header/Marco.h"
#include "../header/tank.h"
#include "../header/Soldier.h"
#include "../header/Ground.h"
#include "../header/Bullet.h"
#include "../header/MapObject.h"
#include "../header/Firework.h"
#include "../header/Grenade.h"
#include "../header/Boss1.h"
#include "../header/boss1_canno.h"
#include "../header/boss1_laser.h"
#include "../header/Prisoner.h"
#include "../header/boss1_fire.h"
#include "../header/RShobu.h"
#include "../header/RShobuBomb.h"
#include <string>
#include <vector>
#include <set>
#include <algorithm>
#include <ctime>

namespace game_framework {
	// function
	extern std::vector<std::vector<std::string>> readCSV(const std::string& filename);
	extern void createPrisoners();
	extern void createRShobus();
	extern void createSoldiers();
	extern void createGrounds();
	extern void createMap();
	extern void removeInactiveSolider();
	extern void addBullet(int x, int y, int speedX, int facingX, int facingY, std::string owner);
	extern void addFirework(int x, int y, std::string direction);
	extern void removeInactives();
	extern void removeMapObject();
	extern void updateCharacter();
	extern void updateUnderCharacterLayer();
	extern void updateUpperCharacterLayer();
	extern void updateMapObject();
	extern void createMapObject();
	extern bool Checkcheckpoint();
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
	extern vector<vector<string>> checkpointcsv;

	// character
	extern const int GRAVITY;
	extern std::set<UINT> keyDowns;
	extern Marco marco;
	extern tank marco_tank;
	extern std::vector <MapObject> MapObjects;
	extern std::vector<Soldier> soldiers;
	extern std::vector<Bullet> bullets;
	extern std::vector<Firework> soldierFireworks;
	extern std::vector<Prisoner> prisoners;
	extern std::vector<RShobu> rshobus;
	extern std::vector<Ground> grounds;
	extern bool scroll;
	extern bool Loading;
	extern vector<vector<string>> groundcsv;
	extern Boss1 boss;
	extern Boss1_laser laser;
}
