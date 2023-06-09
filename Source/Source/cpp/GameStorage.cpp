#include "stdafx.h"
#include "../header/GameStorage.h"
#include <fstream>
#include <sstream>
namespace game_framework {
	void createPickups(void) {
		Pickup::createPickup(100, 200);
		Pickup::createPickup(2000, 200);
		Pickup::createPickup(5000, 200);
		Pickup::createPickup(7000, 200);
	}
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
		prisoners.push_back(Prisoner(1000, 100));
		prisoners.push_back(Prisoner(3000, 100));
		prisoners.push_back(Prisoner(5000, 100));
		prisoners.push_back(Prisoner(7000, 100));
		prisoners.push_back(Prisoner(9000, 100));
	}
	void createRShobus() {
		rshobus.push_back(RShobu(5000, 100));
	}
	void createSoldiers() {
		const int moveSpeed = 1;
		//soldiers.push_back(Soldier(100, 100, moveSpeed));
		//soldiers.push_back(Soldier(200, 200, moveSpeed));
		//soldiers.push_back(Soldier(300, 300, moveSpeed));
		//soldiers.push_back(Soldier(400, 400, moveSpeed));
		//soldiers.push_back(Soldier(500, 500, moveSpeed));
		soldiers.push_back(Soldier(600, 100, moveSpeed));
		soldiers.push_back(Soldier(1000, 500, 1));
		soldiers.push_back(Soldier(1500, 500, 1));
		soldiers.push_back(Soldier(2000, 500, 1));
		soldiers.push_back(Soldier(2500, 500, 1));
		soldiers.push_back(Soldier(3000, 500, 1));
		soldiers.push_back(Soldier(3500, 500, 1));
		soldiers.push_back(Soldier(4000, 500, 1));
		soldiers.push_back(Soldier(4500, 500, 1));
		
	}
	bool isColboxOverlap(ColBox colbox1, ColBox colbox2) {
		return !(colbox1.second.first < colbox2.first.first ||
			colbox1.second.second < colbox2.first.second ||
			colbox2.second.first < colbox1.first.first ||
			colbox2.second.second < colbox1.first.second);
	}
	void collideWithBullet() {
		for (auto &rshobu : rshobus) {
			for (auto &bomb : rshobu.getBombs()) {
				if (marco.IsOverlap_(bomb)) {
					if (!godmode) { marco.dead(); }
				}
			}
		}

		for (auto &grenade : heroGrenades) {
			ColBox emptyColBox = {
				{-1, -1},
				{-1, -1}
			};
			ColBox grenadeColBox = emptyColBox;
			ASSERT(grenadeColBox == emptyColBox);
			ASSERT(&grenadeColBox != &emptyColBox);

			if (grenade.isExpired()) {
				grenadeColBox = grenade.explode();
			}
			else {
				for (auto &soldier : soldiers) {
					if (grenade.IsOverlap_(soldier)) { // soldier overlapped
						ASSERT(grenadeColBox == emptyColBox);
						grenadeColBox = grenade.explode();
						break;
					}
				}
				for (auto &rshobu : rshobus) {
					if (grenade.IsOverlap_(rshobu)) {
						ASSERT(grenadeColBox == emptyColBox);
						grenadeColBox = grenade.explode();
						break;
					}
				}
			}
			
			if (grenadeColBox != emptyColBox) { // check in range soldier
				for (auto &soldier : soldiers) {
					ColBox soldierColBox = soldier.getColBox();
					ASSERT(soldierColBox != emptyColBox);
					if (isColboxOverlap(grenadeColBox, soldierColBox)) {
						soldier.dead();
					}
				}
				for (auto &rshobu : rshobus) {
					ColBox rshobuColBox = rshobu.getColBox();
					ASSERT(rshobuColBox != emptyColBox);
					if (isColboxOverlap(grenadeColBox, rshobuColBox)) {
						rshobu.damge(10);
					}
				}
			}
		}

		for (auto &grenade : enemyGrenades) {
			ColBox emptyColBox = {
				{-1, -1},
				{-1, -1}
			};
			ColBox grenadeColbox = emptyColBox;

			if (grenade.isExpired() || grenade.IsOverlap_(marco)) {
				grenadeColbox = grenade.explode();
			}
			
			if (grenadeColbox != emptyColBox &&
				isColboxOverlap(grenadeColbox, marco.getColBox())
			) {
				marco.dead();
			}
		}

		for (size_t i = 0; i < bullets.size(); i++) {
			if (!bullets[i].isAlive())
				continue;
			if (bullets[i].owner == "enemy" && game_framework::CMovingBitmap::IsOverlap(marco, bullets[i])) {
				marco.dead();
				bullets[i].dead();
				break;
			}
			if (bullets[i].owner == "enemy" && game_framework::CMovingBitmap::IsOverlap(marco_tank, bullets[i])) {
				marco_tank.dead();
				bullets[i].dead();
				break;
			}
			for (size_t j = 0; j < soldiers.size(); j++) {
				if (bullets[i].owner == "hero" &&game_framework::CMovingBitmap::IsOverlap(bullets[i], soldiers[j])) {
					soldiers[j].dead();
					bullets[i].dead();
					break;
				}
			}
			for (size_t j = 0; j < MapObjects.size(); j++) {
				if (bullets[i].owner == "hero" &&bullets[i].IsOverlap_(MapObjects[j])&& MapObjects[j].isAlive()) {
					MapObjects[j].damge(1);;
					bullets[i].dead();
					break;
				}
			}
			for (size_t j = 0; j < rshobus.size(); j++)
				if (bullets[i].owner == "hero" &&game_framework::CMovingBitmap::IsOverlap(bullets[i], rshobus[j])) {
					bullets[i].dead();
					rshobus[j].damge(1);
					break;
				}
			if(bullets[i].owner == "hero" && bullets[i].IsOverlap_(boss)){
				bullets[i].dead();
				boss.damge(1);
				break;
			}
		}
		for (size_t i = 0; i < soldierFireworks.size(); i++) {
			if (game_framework::CMovingBitmap::IsOverlap(marco, soldierFireworks[i])) {
				if (!godmode) { marco.dead(); }
				break;
			}
			if (game_framework::CMovingBitmap::IsOverlap(marco_tank, soldierFireworks[i])) {
				if (!godmode) { marco.dead(); }
				soldierFireworks[i].dead();
				break;
			}
			
		}
		for (size_t i = 0; i < tank_bullets.size(); i++) {
			for (size_t j = 0; j < soldiers.size(); j++) {
				if (game_framework::CMovingBitmap::IsOverlap(*tank_bullets[i], soldiers[j])) {
					soldiers[j].dead();
					(*tank_bullets[i]).dead();
					break;
				}
			}
			for (size_t j = 0; j < MapObjects.size(); j++) {
				if (( *tank_bullets[i]).IsOverlap_(MapObjects[j]) && MapObjects[j].isAlive()) {
					MapObjects[j].damge(1);;
					(*tank_bullets[i]).dead();
					break;
				}
			}
			for (size_t j = 0; j < rshobus.size(); j++)
				if(game_framework::CMovingBitmap::IsOverlap(*tank_bullets[i], rshobus[j])) {
					(*tank_bullets[i]).dead();
					rshobus[j].damge(1);
					break;
				}
			if ((*tank_bullets[i]).IsOverlap_(boss)) {
				(*tank_bullets[i]).dead();
				boss.damge(1);
				break;
			}
		}
		for (size_t i = 0; i < soldierFireworks.size(); i++) {
			if (game_framework::CMovingBitmap::IsOverlap(marco, soldierFireworks[i])) {
				if (!godmode) { marco.dead(); }
				break;
			}
			if (game_framework::CMovingBitmap::IsOverlap(marco_tank, soldierFireworks[i])) {
				if (!godmode) { marco.dead(); }
				soldierFireworks[i].dead();
				break;
			}

		}

		for (auto &pickup : pickups) {
			if (isColboxOverlap(pickup.getAbsRectBox().getColBox(), marco.getColBox())) {
				marco.powerUp();
				pickup.dead();
			}
		}
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
		heroGrenades.erase(std::remove_if(heroGrenades.begin(), heroGrenades.end(), [](const Grenade &grenade) {
			return !grenade.isAlive();
		}), heroGrenades.end());

		enemyGrenades.erase(std::remove_if(enemyGrenades.begin(), enemyGrenades.end(), [](const Grenade &grenade) {
			return !grenade.isAlive();
		}), enemyGrenades.end());

		bullets.erase(std::remove_if(bullets.begin(), bullets.end(), [](const Bullet &bullet) {
			return !bullet.isAlive();
		}), bullets.end());

		soldierFireworks.erase(std::remove_if(soldierFireworks.begin(), soldierFireworks.end(), [](const Firework &firework) {
			return !firework.isAlive();
		}), soldierFireworks.end());

		for (unsigned i = 0; i < tank_bullets.size();)
			if (!tank_bullets[i]->isAlive()) {
				delete tank_bullets[i];
				tank_bullets.erase(tank_bullets.begin() + i);
			}
			else
				i++;
		rshobus.erase(std::remove_if(rshobus.begin(), rshobus.end(), [](const RShobu &rshobu) {
			return !rshobu.isAlive();
		}), rshobus.end());

		pickups.erase(std::remove_if(pickups.begin(), pickups.end(), [](const Pickup &pickup) {
			return !pickup.isAlive();
		}), pickups.end());
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
		for (size_t i = 0; i < prisoners.size(); i++) {
			prisoners[i].draw();
		}
		for (size_t i = 0; i < soldiers.size(); i++) {
			soldiers[i].draw();
		}
		for (size_t i = 0; i < rshobus.size(); i++) {
			rshobus[i].draw();
		}
		boss.draw();
		marco_tank.draw();
		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].draw();
		}
		for (auto &grenade : heroGrenades) {
			grenade.draw();
		}
		for (auto &grenade : enemyGrenades) {
			grenade.draw();
		}
		for (unsigned i = 0; i < tank_bullets.size(); i++) {
			tank_bullets[i]->move();
			tank_bullets[i]->draw();
		}
		for (size_t i = 0; i < soldierFireworks.size(); i++) {
			soldierFireworks[i].draw();
		}
		for (auto &pickup : pickups) {
			pickup.draw();
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
		vector<bool> test,test2;
		/*
		for (unsigned i = 0; i < soldiers.size(); i++)
			test.push_back(soldiers[i].isAlive());
		for (int i = soldiers.size(); i > 0; --i) {
			if (!soldiers[i - 1].isAlive()) {
				soldiers.erase(soldiers.begin() + i - 1);
				for (unsigned j = 0; j < soldiers.size(); j++)
					test2.push_back(soldiers[j].isAlive());
			}
		}
		*/

		
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
	void resetWorld(void) {

		selectIndex = 0;
		ViewPointX = 0;
		ViewPointY = 580;
		MapScrollSpeed = 10;
		scroll = false;
		marco = Marco(300, 100, 6);
		MapObjects = std::vector<MapObject>();
		soldiers = std::vector<Soldier>();
		bullets = std::vector<Bullet>();
		tank_bullets = std::vector<tank_bullet *>();
		soldierFireworks = std::vector<Firework>();
		prisoners = std::vector<Prisoner>();
		rshobus = std::vector<RShobu>();
		grounds = std::vector<Ground>();
		marco_tank = tank(300, 100, 6);
		Loading = false;
		ViewPointYInit = 580;
		boss = Boss1(9900, -190);
		Driving = false;
		tank_barrel_angle = 0;
		godmode = false;
		isDisplayInfo = false;
		heroGrenades = std::vector<Grenade>();
		enemyGrenades = std::vector<Grenade>();
		pickups = std::vector<Pickup>();

		boss.init();
		background.LoadBitmapByString({ "resources/backgrounds/bg_mainmenu.bmp" }, RGB(0, 0, 0));
		arrow.LoadBitmapByString({ "resources/bmp/arrow.bmp" }, RGB(255, 255, 255));
		background.SetTopLeft(0, 0);
		for (int i = 0; i < 4; i++) {
			CMovingBitmap btn;
			btn.LoadBitmapByString({ "resources/menus/btn_generic.bmp" }, RGB(0, 0, 0));
			btn.SetTopLeft(540, 70 * i + 175);
			mainmenuButtons.push_back(btn);
		}
		int position[5] = { 185,255,325,400,500 };
		arrow.SetTopLeft(430, position[selectIndex] - 35);
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
		createMap();
		createGrounds();
		createSoldiers();
		createMapObject();
		createPrisoners();
		createRShobus();
		createPickups();
		marco.init();
		marco_tank.init();
		for (size_t i = 0; i < soldiers.size(); i++) {
			soldiers[i].init();
		}
		for (size_t i = 0; i < MapObjects.size(); i++) {
			MapObjects[i].init();
		}
		for (size_t i = 0; i < prisoners.size(); i++) {
			prisoners[i].init();
		}
		for (size_t i = 0; i < rshobus.size(); i++) {
			rshobus[i].init();
		}






		/*
		ViewPointX = 0;
		ViewPointY = 500;
		
		scroll = false;
		Driving = false;
		tank_barrel_angle = 0;
		marco.respawn();
		//marco_tank.reset();
		//boss.reset();
		heroGrenades = std::vector<Grenade>();
		enemyGrenades = std::vector<Grenade>();
		bullets = std::vector<Bullet>();
		soldierFireworks = std::vector<Firework>();
		tank_bullets = std::vector<tank_bullet *>();
		rshobus = std::vector<RShobu>();
		pickups = std::vector<Pickup>();
		createRShobus();
		createPickups();
		for (size_t i = 0; i < MapObjects.size(); i++) {
			MapObjects[i].reset();
		}
		for (size_t i = 0; i < soldiers.size(); i++) {
			soldiers[i].reset();
		}
		for (size_t i = 0; i < prisoners.size(); i++) {
			prisoners[i].reset();
		}
		*/
		/*
		heroGrenades
		enemyGrenades
		bullets
		soldierFireworks
		tank_bullets
		rshobus
		pickups
		*/
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
	std::vector<tank_bullet *> tank_bullets;
	std::vector<Firework> soldierFireworks;
	std::vector<Prisoner> prisoners;
	std::vector<RShobu> rshobus;
	std::vector<Ground> grounds;
	tank marco_tank(300, 100, 6);
	bool Loading = false;
	int ViewPointYInit = 580;
	Boss1 boss(9900,- 190);
	bool Driving = false;
	int tank_barrel_angle = 0;
	bool godmode = false;
	bool isDisplayInfo = false;
	std::vector<Grenade> heroGrenades;
	std::vector<Grenade> enemyGrenades;
	std::vector<Pickup> pickups;
}
