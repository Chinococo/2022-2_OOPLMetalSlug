#include "stdafx.h"
#include "../header/GameStorage.h"
#include "../header/boss1_canno.h"

boss1_canno::boss1_canno(int _x, int _y) : Character(_x, _y, 0)
{
	this->x = _x;
	this->y = _y;
	this->laser = new Boss1_laser(x, y);
}

void boss1_canno::Setaction(string _action)
{
}

void boss1_canno::init()
{
	this->laser->init();
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
	this->laser->move();
	for (unsigned i = 0; i < fire.size(); i++) {
		this->fire[i]->move();
	}
	position = static_cast<int>(action) % 2;
	int aiDelay = (state == "map1") ? 5000 : 2500; 
	if (clock() - start_AI > aiDelay&&Done) {
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
			if (rand() % 2) {
				if (position) {//up
					action = Action::AttackUp;
				}
				else {
					action = Action::AttackLow;
				}
			}
			else {
				if (position) {//up
					action = Action::LaserUp;
				}
				else {
					action = Action::LasetLow;
				}
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
		if (action == Action::LaserUp) {
			this->laser->isAlive = true;
			this->laser->setXY(x, 20 + y);
		}
		if (action == Action::LasetLow) {
			this->laser->isAlive = true;
			this->laser->setXY(x, y + 100);
		}
		if (action == Action::AttackUp) {
			Boss1_fire* temp = new Boss1_fire(x, y);
			
;			temp->isAlive = true;
			temp->setXY(x, 20 + y);
			temp->init();
			this->fire.push_back(temp);
		}
		if (action == Action::AttackLow) {
			Boss1_fire* temp = new Boss1_fire(x, y);
			temp->isAlive = true;
			temp->setXY(x, 100 + y);
			temp->init();
			this->fire.push_back(temp);
		}
			
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
	this->ShowBitmap(1.7);
	if(this->laser->isAlive)
		this->laser->draw();
	for (unsigned i = 0; i < fire.size(); ) {
		if (this->fire[i]->isAlive)
			this->fire[i]->draw(), i++;
		else
			fire.erase(fire.begin() + i);
	}
	
}

