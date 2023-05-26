#include "stdafx.h"
#include "../header/GameStorage.h"
#include <fstream>
#include <sstream>
namespace game_framework {
	std::vector<std::vector<std::string>> readCSV(const std::string& filename) {
		std::vector<std::vector<std::string>> data;
		std::ifstream file(filename);

		if (!file.is_open()) {
			return data;
		}

		std::string line;
		while (std::getline(file, line)) {
			std::vector<std::string> row;
			std::string cell;
			std::stringstream lineStream(line);

			while (std::getline(lineStream, cell, ',')) {
				row.push_back(cell);
			}
			if(row.size()>0)
				data.push_back(row);
		}

		file.close();
		
		return data;
	}
	void createPrisoners() {
		prisoners.push_back(Prisoner(200, 100));
	}
	void createRShobus() {
		rshobus.push_back(RShobu(300, 100));
	}
	void createSoldiers() {
		const int moveSpeed = 1;
		soldiers.push_back(Soldier(100, 100, moveSpeed));
		//soldiers.push_back(Soldier(200, 200, moveSpeed));
		//soldiers.push_back(Soldier(300, 300, moveSpeed));
		//soldiers.push_back(Soldier(400, 400, moveSpeed));
		//soldiers.push_back(Soldier(500, 500, moveSpeed));
		soldiers.push_back(Soldier(600, 100, moveSpeed));
		/*
		soldiers.push_back(Soldier(1000, 500, 1));
		soldiers.push_back(Soldier(1500, 500, 1));
		soldiers.push_back(Soldier(2000, 500, 1));
		soldiers.push_back(Soldier(2500, 500, 1));
		soldiers.push_back(Soldier(3000, 500, 1));
		soldiers.push_back(Soldier(3500, 500, 1));
		soldiers.push_back(Soldier(4000, 500, 1));
		soldiers.push_back(Soldier(4500, 500, 1));
		*/
	}
	void createGrounds() {
		/* 地板 */
		for (unsigned i = 1; i < groundcsv.size(); i++) {
			if (std::stoi(groundcsv[i][0]) != 1)
				continue;
			grounds.push_back(Ground({ std::stoi(groundcsv[i][1]),std::stoi(groundcsv[i][2]) }, { std::stoi(groundcsv[i][3]),std::stoi(groundcsv[i][4]) }));
		}

		/*牆壁*/
		grounds.push_back(Ground({ 0,0 }, { 0,600 }));

		/*Debug專用*/
		//grounds.push_back(Ground({ 5750,515 }, { 10000,515 }));

	}
	void createMap() {
		background_mission1.LoadBitmapByString({ "resources/maps/background4.bmp" }, RGB(255, 255, 255));
		background_mission1.SetTopLeft(8000, -100);
		std::vector<std::tuple<std::vector<std::string>, std::vector<std::pair<int, int>>, COLORREF,bool>> layer;
		layer.push_back({ {"resources/maps/water_01_01.bmp","resources/maps/water_01_02.bmp","resources/maps/water_01_03.bmp","resources/maps/water_01_04.bmp"
			,"resources/maps/water_01_05.bmp","resources/maps/water_01_06.bmp","resources/maps/water_01_07.bmp"},{{5035,485},{5035,485},{5035,485},{5035,485},{5035,485},{5035,485},{5035,485}} , RGB(255, 255, 255),true });
		layer.push_back({ {"resources/maps/background2.bmp"},{{3650,330}} , RGB(255, 255, 255),false });
		layer.push_back({ {"resources/maps/background1.bmp"},{{3500,330}} , RGB(255, 255, 255),false });
		layer.push_back({ {"resources/maps/map1_1.bmp"},{{0,15}} , RGB(255,255,255),false });
		layer.push_back({ {"resources/maps/background.bmp"},{{5400,0}} , RGB(255, 255, 255),false });
		layer.push_back({ {"resources/maps/background3.bmp"},{{6000,-140}} , RGB(255, 255, 255),false });
		UnderCharacter.clear();
		for (unsigned i = 0; i < layer.size(); i++) {
			CMovingBitmap temp;
			temp.LoadBitmapByString(std::get<0>(layer[i]), std::get<2>(layer[i]));
			if (get<3>(layer[i])) {
				temp.SetAnimation(200,false);
				temp.ToggleAnimation();
			}
				
			UnderCharacter.push_back({ temp,std::get<1>(layer[i]) });
		}
		UpperCharacter.clear();
		layer.clear();
		layer.push_back({ {"resources/maps/background2.bmp"},{{3650,330}} , RGB(255, 255, 255) ,false });
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
	void addFirework(int x, int y, std::string direction) {
		Firework firework(x, y, direction);
		firework.init();
		soldierFireworks.push_back(firework);
	}
	void removeInactives() {
		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &bullet) {
			return !bullet.isAlive();
		}), bullets.end());

		soldierFireworks.erase(std::remove_if(soldierFireworks.begin(), soldierFireworks.end(), [](const Firework &firework) {
			return !firework.isAlive();
		}), soldierFireworks.end());

		/* bug
		prisoners.erase(std::remove_if(prisoners.begin(), prisoners.end(), [](const Prisoner &prisoner) {
			return !prisoner.isAlive();
		}), prisoners.end());
		*/

		rshobus.erase(std::remove_if(rshobus.begin(), rshobus.end(), [](const RShobu &rshobu) {
			return !rshobu.isAlive();
		}), rshobus.end());
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
		//if (marco.GetLeft() + abs(ViewPointX) > 8500 && marco.GetLeft() + abs(ViewPointX) < 9000)
		//	background_mission1.SetTopLeft(background.GetLeft() + (marco.GetLeft() + abs(ViewPointX) - 8500) / 1000, background_mission1.GetTop());
		//else
		//	background_mission1.SetTopLeft((ViewPointX + 9400 - background_mission1.GetWidth()), background_mission1.GetTop());
		//background_mission1.ShowBitmap();
		for (unsigned i = UnderCharacter.size() - 1;; i--) {
			int now_index = std::get<0>(UnderCharacter[i]).GetFrameIndexOfBitmap();
			std::get<0>(UnderCharacter[i]).SetTopLeft(
				ViewPointX + std::get<1>(UnderCharacter[i])[now_index].first,
				ViewPointY - background.GetHeight() + std::get<1>(UnderCharacter[i])[now_index].second
			);
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
		std::vector<std::vector<std::string>> csv = readCSV("resources/csv/mapobject.csv");
		for (unsigned i = 1; i < csv.size(); i++) {
			vector<std::string> image;
			for (unsigned index = 10; index < csv[i].size(); index++) {
				if (csv[i][index] == "")
					break;
				image.push_back(csv[i][index]);
			}
			if (std::stoi(csv[i][0]) == 1) {
				MapObjects.push_back(MapObject(std::stoi(csv[i][1]), std::stoi(csv[i][2]), std::stoi(csv[i][4]), image, csv[i][5], std::stoi(csv[i][3]), { {std::stoi(csv[i][6]),std::stoi(csv[i][7])} ,{std::stoi(csv[i][8]),std::stoi(csv[i][9])} }));
			}
				
		}
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
	bool Checkcheckpoint() {
		for (unsigned i = 1; i < checkpointcsv.size(); i++) {
		
			if (checkpointcsv[i][1] == "boss1"&&abs(ViewPointX) >= std::stoi(checkpointcsv[i][3])) 
				return true;
			
		
			for (unsigned j = 0; j < MapObjects.size(); j++) {
				if (MapObjects[j].GetName() != checkpointcsv[i][2]|| checkpointcsv[i][1]!="MapObject"|| checkpointcsv[i][0] != "1")
					continue;
				if(MapObjects[j].isAlive() && abs(ViewPointX) >= std::stoi(checkpointcsv[i][3]))
					return true;
				
			}
		}
		return false;
				
	}
	vector<vector<string>> checkpointcsv = readCSV("resources/csv/checkpoint.csv");
	vector<vector<string>> groundcsv = readCSV("resources/csv/ground.csv");
	std::string state = "init";
	int selectIndex = 0;
	CMovingBitmap background;
	CMovingBitmap arrow;
	CMovingBitmap background_mission1;
	std::vector<CMovingBitmap> mainmenuButtons;
	int ViewPointX = 0 ;
	int ViewPointY = 580;
	int MapScrollSpeed = 10;
	bool scroll = false;
	std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> UnderCharacter;
	std::vector<std::pair<CMovingBitmap, std::vector<std::pair<int, int>>>> UpperCharacter;
	const int GRAVITY = 1;
	std::set<UINT> keyDowns;
	Marco marco(300, 100, 6);
	std::vector <MapObject> MapObjects;
	std::vector<Soldier> soldiers;
	std::vector<Bullet> bullets;
	std::vector<Firework> soldierFireworks;
	std::vector<Prisoner> prisoners;
	std::vector<RShobu> rshobus;
	std::vector<Ground> grounds;
	bool Loading = false;
	int ViewPointYInit = 580;
	Boss1 boss(9900,- 190);
	
}
