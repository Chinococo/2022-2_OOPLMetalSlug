#include "stdafx.h"
#include "../header/GameStorage.h"

namespace game_framework {
	void createSoldiers() {
		soldiers.push_back(Soldier(500, 500, 4));
	}
	void createGrounds() {
		grounds.push_back(Ground({ 0,475 }, { 1820,475 }));
		grounds.push_back(Ground({ 1820,400 }, { 1820,800 }));
		grounds.push_back(Ground({ 1750,550 }, { 5000,550 }));//斜坡
		grounds.push_back(Ground({ 2300,430 }, { 2550,430 }));//斜坡
		grounds.push_back(Ground({ 2520,320 }, { 3100,320 }));//斜坡
		grounds.push_back(Ground({ 3000,425 }, { 3150,425 }));//斜坡
		grounds.push_back(Ground({ 3150,325 }, { 3600,325 }));//斜坡
		grounds.push_back(Ground({ 3600,325 }, { 4200,325 }));//斜坡
		grounds.push_back(Ground({ 4100,430 }, { 4280,430 }));//斜坡
		//grounds.push_back(Ground({ 410,450 }, { 410,800 }));
		grounds.push_back(Ground({ 0,0 }, { 0,600 }));//左邊的牆壁
		//grounds.push_back(Ground({ 700,0 }, { 700,600 }));//右邊的牆壁
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
	void removeInactiveSolider() {
		for (size_t i = 0; i < soldiers.size();) {
			if (!soldiers[i].isAlive()) {
				soldiers.erase(soldiers.begin()+i);
			}
			else
				i++;
		}
	}
	
	std::string state = "init";
	int selectIndex = 0;
	CMovingBitmap background;
	CMovingBitmap arrow;
	std::vector<CMovingBitmap> mainmenuButtons;
	int ViewPointX = 0;
	int ViewPointY = 580;
	int MapScrollSpeed = 10;
	bool scroll = false;
	std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> map;

	const int GRAVITY = 1;
	std::set<UINT> keyDowns;
	Marco marco(300, 300, 6);
	std::vector<Soldier> soldiers;
	std::vector<Bullet> bullets;
	std::vector<Ground> grounds;
}
