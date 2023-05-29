#include "stdafx.h"
#include "../header/GameStorage.h"
#include "../header/boss1_canno.h"
#include "../header/tank_ barrel.h"

tank_barrel::tank_barrel(int _x, int _y)
{
	x = _x;
	y = _y;
}

void tank_barrel::init()
{
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	pair<int, int> range;
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "tank_barrel")
			continue;
		string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };
		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + std::to_string(i) + ".bmp");
		}
	}
	LoadBitmapByString(paths, RGB(255, 255, 255));
}

void tank_barrel::update(int _x,int _y)
{
	attacking = keyDowns.count(0x5A); // Z
	if (attacking&&clock() - start > 50) {
		fire = true;
		start = clock();
	}
	else {
		fire = false;
	}
	this->x = _x;
	this->y = _y;
	if (fire) {
		SetTopLeft(ViewPointX + x, y - ViewPointYInit + ViewPointY+20);
	}
	else {
		SetTopLeft(ViewPointX + x+30, y - ViewPointYInit + ViewPointY + 50);
	}
	
	SetFrameIndexOfBitmap(tank_barrel_angle +fire*32);
}

void tank_barrel::draw() {
	ShowBitmap(1.5);
}

int tank_barrel::GetAngele()
{
	return tank_barrel_angle;
}

void tank_barrel::SetAngele(int _angle)
{
	tank_barrel_angle = _angle;
}
