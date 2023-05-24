#include "stdafx.h"
#include "../header/GameStorage.h"

Boss1::Boss1(int _x, int _y) : Character(_x, _y,0)
{
	this->x = _x;
	this->y = _y;
	this->canno = new boss1_canno(x + 450, y+270);
}
void Boss1::init() {
	vector<vector<string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;
	for (unsigned line = 0; line < csv.size(); line++) {
		if (csv[line].size() == 0)
			continue;

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
	this->canno->init();
}

void Boss1::update()
{
	//canno->Move();
	canno->update();
}

void Boss1::draw()
{
	this->SetTopLeft(ViewPointX + x, y - ViewPointYInit + ViewPointY);
	this->ShowBitmap(2);
	this->canno->draw();
}
