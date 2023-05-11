#include "stdafx.h"
#include "../header/GameStorage.h"

namespace game_framework {
	void createSoldiers() {
		soldiers.push_back(Soldier(500, 500, 4));
	}
	void createGrounds() {
		/* 地板 */
		grounds.push_back(Ground({ 0,475 }, { 1820,475 }));
		grounds.push_back(Ground({ 1820,400 }, { 1820,800 }));
		grounds.push_back(Ground({ 1750,550 }, { 5000,550 }));
		grounds.push_back(Ground({ 2300,430 }, { 2550,430 }));
		grounds.push_back(Ground({ 2520,320 }, { 3100,320 }));
		grounds.push_back(Ground({ 2930,425 }, { 3150,425 }));
		grounds.push_back(Ground({ 3150,325 }, { 3600,325 }));
		grounds.push_back(Ground({ 3600,325 }, { 4200,325 }));
		grounds.push_back(Ground({ 4050,430 }, { 4250,430 }));

		/*牆壁*/
		grounds.push_back(Ground({ 0,0 }, { 0,600 }));

		/*Debug專用*/
		grounds.push_back(Ground({ 4100,430 }, { 10000,430 }));

	}
	void createMap() {
		std::vector<std::tuple<std::vector<std::string>, std::vector<std::pair<int, int>>, COLORREF>> layer;
		layer.push_back({ {"resources/maps/background2.bmp"},{{3650,330}} , RGB(255, 255, 255) });
		layer.push_back({ {"resources/maps/background1.bmp"},{{3500,330}} , RGB(255, 255, 255) });
		layer.push_back({ {"resources/maps/map1_1.bmp"},{{0,15}} , RGB(255,255,255) });
		layer.push_back({ {"resources/maps/background.bmp"},{{5400,0}} , RGB(255, 255, 255) });
		UnderCharacter.clear();
		for (unsigned i = 0; i < layer.size(); i++) {
			CMovingBitmap temp;
			temp.LoadBitmapByString(std::get<0>(layer[i]), std::get<2>(layer[i]));
			UnderCharacter.push_back({ temp,std::get<1>(layer[i]) });
		}
		UpperCharacter.clear();
		layer.clear();
		layer.push_back({ {"resources/maps/background2.bmp"},{{3650,330}} , RGB(255, 255, 255) });
		//layer.push_back({ {"resources/maps/water_01_01.bmp","resources/maps/water_01_02.bmp","resources/maps/water_01_03.bmp","resources/maps/water_01_04.bmp"
		//	,"resources/maps/water_01_05.bmp","resources/maps/water_01_06.bmp","resources/maps/water_01_07.bmp"},{{5035,500},{5035,500},{5035,500},{5035,500},{5035,500},{5035,500},{5035,500}} , RGB(255, 255, 255) });
		for (unsigned i = 0; i < layer.size(); i++) {
			CMovingBitmap temp;
			temp.LoadBitmapByString(std::get<0>(layer[i]), std::get<2>(layer[i]));
			UpperCharacter.push_back({ temp,std::get<1>(layer[i]) });
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
	void removeMapObject()
	{
		for (size_t i = 0; i < MapObjects.size();) {
			if (!MapObjects[i].isAlive()) {
				MapObjects.erase(MapObjects.begin() + i);
			}
			else
				i++;
		}
	}
	void updateCharacter()
	{
		for (size_t i = 0; i < soldiers.size(); i++) {
			soldiers[i].draw();
		}
		marco.draw();
		
		
	}
	void updateUnderCharacterLayer()
	{
		for (unsigned i = UnderCharacter.size() - 1;; i--) {
			int now_index = std::get<0>(UnderCharacter[i]).GetFrameIndexOfBitmap();
			std::get<0>(UnderCharacter[i]).SetTopLeft(ViewPointX + std::get<1>(UnderCharacter[i])[now_index].first,
				ViewPointY - background.GetHeight() + std::get<1>(UnderCharacter[i])[now_index].second);
			std::get<0>(UnderCharacter[i]).ShowBitmap();
			if (i == 0)
				break;
		}
	}
	void updateUpperCharacterLayer()
	{
		for (unsigned i = UpperCharacter.size() - 1;; i--) {
			int now_index = std::get<0>(UpperCharacter[i]).GetFrameIndexOfBitmap();
			std::get<0>(UpperCharacter[i]).SetTopLeft(ViewPointX + std::get<1>(UpperCharacter[i])[now_index].first,
				ViewPointY - background.GetHeight() + std::get<1>(UpperCharacter[i])[now_index].second);
			std::get<0>(UpperCharacter[i]).ShowBitmap();
			if (i == 0)
				break;
		}
		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].draw();
		}
	}
	void updateMapObject()
	{
		for (size_t i = 0; i < MapObjects.size(); i++)
			MapObjects[i].update();
	}
	void createMapObject()
	{
		MapObjects.push_back(MapObject(4850, 180, 10, { "resources/maps/enemy_platform_1.bmp","resources/maps/enemy_platform_1_broken.bmp" }));
		MapObjects.push_back(MapObject(5490, 0, 10, { "resources/maps/enemy_buliding_1.bmp","resources/maps/enemy_buliding_1_broken.bmp" }));
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
	int ViewPointX = -4800;
	int ViewPointY = 580;
	int MapScrollSpeed = 10;
	bool scroll = false;
	std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> UnderCharacter;
	std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> UpperCharacter;
	const int GRAVITY = 1;
	std::set<UINT> keyDowns;
	Marco marco(300, 300, 6);
	std::vector < MapObject> MapObjects;
	std::vector<Soldier> soldiers;
	std::vector<Bullet> bullets;
	std::vector<Ground> grounds;
	bool Loading = false;
}
