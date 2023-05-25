#pragma once
#include "../../Library/gameutil.h"
using namespace game_framework;
class MapObject :public Character
{
public:
	MapObject(int _x, int _y, int _hp, vector<string> _path, string _name,int _destry_animation_index = -1);
	MapObject(int _x, int _y, int _hp, vector<string> _path, string _name, int _destry_animation_index = -1, pair<pair<int, int>, pair<int, int>> = { {-1,-1},{-1,-1} });
	int GetX();
	string GetName();
	void update();
	bool isAlive();
	void collideWithBullet();
	void init();
protected:
	int hp;
	int now_hp;
	int x;
	int y;
	clock_t start;
	int destry_animation_index;
	vector<string> path;
	string name;
};

