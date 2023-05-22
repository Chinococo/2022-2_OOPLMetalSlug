#include "stdafx.h"
#include "../header/GameStorage.h"
#include "..\header\boss1_canno.h"

boss1_canno::boss1_canno(int _x, int _y) : Character(_x, _y, 0)
{
	this->x = _x;
	this->y = _y;
}

void boss1_canno::Setaction(string _action)
{
}

void boss1_canno::init()
{
	vector<vector<string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;
	for (unsigned line = 0; line < csv.size(); line++) {
		if (csv[line][0] != "boss1")
			continue;
		int delay = std::stoi(csv[line][3]);
		string prefix = csv[line][2];
		range = { std::stoi(csv[line][1].substr(0, csv[line][1].find('~'))), std::stoi(csv[line][1].substr(csv[line][1].find('~') + 1)) };
		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + std::to_string(i) + ".bmp");
		}
		animationRanges.push_back(range);
		animationDelays.push_back(delay);
	}
	LoadBitmapByString(paths, RGB(255, 255, 255));
	animationRange = animationRanges[static_cast<int>(action)];
	animationDelay = animationDelays[static_cast<int>(action)];
}

void boss1_canno::update()
{
}

void boss1_canno::draw()
{
}
