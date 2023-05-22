#include "stdafx.h"
#include "../header/GameStorage.h"
#include "../header/boss1_canno.h"

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
		if (csv[line][0] != "boss1_canno")
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
	SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
}
void boss1_canno::Move() {
	position = static_cast<int>(action) % 2;
	if (clock() - start_AI > 5000&&Done) {
		lastAction = action;
		start_AI = clock();
		if (rand() % 4 == 0) {
			if (position) {//up
				action = Action::MovingDown;
			}
			else {
				action = Action::Movingup;
			}
		}
		else {
			if (position) {//up
				action = Action::AttackUp;
			}
			else {
				action = Action::AttackLow;
			}
		}
		
	}
	else if(Done&&action!= Action::IDLEUp&&action != Action::IDLEDown){
		
		if (position) {//up
			action = Action::IDLEUp;
		}
		else {
			action = Action::IDLEDown;
		}
	}
	if (lastAction != action) {
		lastAction = action;
		Done = false;
		animationRange = animationRanges[static_cast<int>(action)];
		animationDelay = animationDelays[static_cast<int>(action)];
		SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
	}
	
}
void boss1_canno::update()
{
	
	flip = 0;
	animationflipBias = 0;
	if ((((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first))) == 0) {
		Done = true;
		return;
	}
		
	if (clock() - start > animationDelay) {
		int t = GetFrameIndexOfBitmap();
		SetFrameIndexOfBitmap(((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first)) + animationRange.first + ((flip) ? animationflipBias : 0));
		start = clock();
	}
}
void boss1_canno::draw()
{
	this->SetTopLeft(ViewPointX + x, y - ViewPointYInit + ViewPointY);
	this->ShowBitmap(1.6);
}
