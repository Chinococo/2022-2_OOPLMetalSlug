#include "stdafx.h"
#include "../header/GameStorage.h"
#include "cmath"
using namespace game_framework;
MapObject::MapObject(int _x, int _y, int _hp, vector<string> _path,  string _name, int _destry_animation_index) {

	//this->SetTopLeft(_x, _y);
	this->x = _x;
	this->y = _y;
	this->hp = _hp;
	this->now_hp = _hp;
	this->path = _path;
	this->destry_animation_index = _destry_animation_index;
	this->start = clock();
	this->name = _name;
}

int MapObject::GetX()
{
	return x;
}

string MapObject::GetName()
{
	return name;
}

void MapObject::update(){
	collideWithBullet();
	if (this->destry_animation_index != -1 && this->GetFrameIndexOfBitmap() >= this->destry_animation_index) {
		if (this->now_hp > 0 && clock() - start > 100) {
			start = clock();
			this->now_hp -= 1;
		}

	}
	this->SetFrameIndexOfBitmap(static_cast<int>(std::floor(static_cast<double>(static_cast<double>(hp - now_hp) / hp) * (this->GetFrameSizeOfBitmap() - 1))));
	this->SetTopLeft(ViewPointX + x, y);
	//if (this->isAlive())
		this->ShowBitmap();
	//else
	//	this->UnshowBitmap();
}
bool MapObject::isAlive() {
	return  now_hp != 0;
}

void MapObject::init()
{
	this->LoadBitmapByString(path, RGB(255, 255, 255));
	this->SetTopLeft(x, y);
}

void MapObject::collideWithBullet() {
	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i].owner == "hero" && IsOverlap(*this, bullets[i]) && isAlive()) {
			now_hp -= 1;
		}
	}
}