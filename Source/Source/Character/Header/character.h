#pragma once
#include "object.h"
#include "../Header/bullet.h"
#include "../../../Library/gameutil.h"
#include <vector>

class Character : public Object {
protected:
	Character();
	game_framework::CMovingBitmap standTexture;
	game_framework::CMovingBitmap fireTexture;
	game_framework::CMovingBitmap slashTexture;
	game_framework::CMovingBitmap jumpUpTexture;
	game_framework::CMovingBitmap landTexture;
	int movementSpeed;
	int jumpDuration;
	int timeJumped;
	std::vector<Bullet> activeBullets;
public:
	void jumpUpward();
	void moveLeft();
	void moveRight();
	void fireWeapon();
	void slashNearby();
	bool isReadyToLand();
};
