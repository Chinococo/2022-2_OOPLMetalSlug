#include "stdafx.h"
#include "../header/GameStorage.h"

namespace game_framework {
	void createSoldiers() {
		soldiers.push_back(Soldier(500, 500, 5));
	}
	void createGrounds() {
		grounds.push_back(Ground({ 0,600 }, { 800,400 }));
		//grounds.push_back(Ground({ 410,450 }, { 410,800 }));
		grounds.push_back(Ground({ 0,550 }, { 1000,550 }));
		grounds.push_back(Ground({ 0,0 }, { 0,600 }));
		grounds.push_back(Ground({ 780,0 }, { 780,600 }));
	}
	void createMap() {
		std::vector<std::tuple<std::vector<std::string>, std::vector<std::pair<int, int>>, COLORREF>> layer;
		layer.push_back({ {"resources/maps/background2.bmp"},{{3650,330}} , RGB(255, 255, 255) });
		layer.push_back({ {"resources/maps/background1.bmp"},{{3500,330}} , RGB(255, 255, 255) });
		//layer.push_back({ {"resources/maps/test2.bmp"},{{5685,22}} , RGB(0, 0, 0) });//破壞
		//layer.push_back({ {"resources/maps/test1.bmp"},{{5490,15}} , RGB(0, 0, 0) });//破壞
		layer.push_back({ {"resources/maps/map1_1.bmp"},{{0,15}} , RGB(0, 0, 0) });
		//layer.push_back({ {"resources/maps/test0.bmp"},{{5490,15}} , RGB(255, 255, 255) });//原本
		//layer.push_back({ {"resources/maps/test3.bmp"},{{5840,15}} , RGB(255, 255, 255) });//原本
		map.clear();
		for (unsigned i = 0; i < layer.size(); i++) {
			CMovingBitmap temp;
			temp.LoadBitmapByString(std::get<0>(layer[i]), std::get<2>(layer[i]));
			map.push_back({ temp,std::get<1>(layer[i]) });
		}
	}
	void addBullet(int x, int y, int speedX, int facingX, int facingY, std::string owner) {
		Bullet bullet(x, y, speedX, facingX, facingY, owner);
		bullet.init();
		bullets.push_back(bullet);
	}
	void removeInactiveBullets() {
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &bullet) {
			return !bullet.isAlive();
		}), bullets.end());
	}

	std::string state = "init";
	int selectIndex = 0;
	CMovingBitmap background;
	CMovingBitmap arrow;
	std::vector<CMovingBitmap> mainmenuButtons;
	int ViewPointX = 0;
	int ViewPointY = 580;
	int MapScrollSpeed = 10;
	std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> map;

	const int GRAVITY = 1;
	std::set<UINT> keyDowns;
	Marco marco(300, 300, 10);
	std::vector<Soldier> soldiers;
	std::vector<Bullet> bullets;
	std::vector<Ground> grounds;
}
