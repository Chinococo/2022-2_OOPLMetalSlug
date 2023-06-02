#include "stdafx.h"
#include <chrono>
#include "../header/GameStorage.h"

using namespace game_framework;

Marco::Marco(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {
	
}

void Marco::init() {
	// order following enum class Action
	// IDLE, MOVE, JUMP, LOOK_UP, SHOOT, SHOOT_UP, SHOOT_DOWN, KNIFE, GRENADE, CROUCH_SHOOT, CROUCH_SHOOT_UP, CROUCH_KNIFE, CROUCH_GRENADE, DIE
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "marco")
			continue;
		int delay = std::stoi(csv[i][3]);
		string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr( csv[i][1].find('~')+1)) };
		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + std::to_string(i) + ".bmp");
		}
		animationRanges.push_back(range);
		animationDelays.push_back(delay);
	}
	animationflipBias = range.second;

	/*filp*/
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "marco")
			continue;
		int delay = std::stoi(csv[i][3]);
		string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };
		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix +"flip_"+ std::to_string(i) + ".bmp");
		}
		animationRanges.push_back(range);
		animationDelays.push_back(delay);
	}
	LoadBitmapByString(paths, RGB(0, 0, 0));
	animationRange = animationRanges[static_cast<int>(action)];
	animationDelay = animationDelays[static_cast<int>(action)];
}

void Marco::update() {
	if (!dying&&!Driving) {
		control();
		move();
		updateAction();
		changeAnimation();
		updateAnimation();
	}
	else if(!Driving){
		action = Action::DIE;
		changeAnimation();
		updateAnimation();
		if (clock() - deathTimer > 1000) {
			alive = false;
		}
	}
}

void Marco::respawn() {
	alive = true;
	dying = false;
	once = false;
	velocityY = 0;
	movingLeft = false;
	movingRight = false;
	jumping = false;
	inAir = false;
	lookingUp = false;
	attacking = false;
	knifing = false;
	throwingGrenade = false;
	pressingDown = false;
	nearEnemy = false;
	lastAttackTime = clock();
	action = Action::IDLE;
	lastAction = Action::IDLE;
	x = 100;
	y = 300;
	dx = 0;
	dy = 0;
	facingX = 1;
	facingY = 0;
	alive = true;
	dying = false;
	flip = false;
	deathTimer = clock();
	std::pair<std::pair<int, int>, std::pair<int, int>> CollideBox = { {-1,-1},{-1,-1} };
	start = clock();
}

void Marco::control() {
	clock_t currentTime = clock();
	if (!Driving) {
		scroll = (this->GetLeft() > 400);
	}
	else {
		x, y = marco_tank.GetLeft(), marco_tank.GetTop();
	}
	movingLeft = keyDowns.count(VK_LEFT);
	movingRight = keyDowns.count(VK_RIGHT);
	jumping = keyDowns.count(VK_SPACE);
	lookingUp = keyDowns.count(VK_UP);
	pressingDown = keyDowns.count(VK_DOWN);
	attacking = keyDowns.count(0x5A); // Z
	throwingGrenade = keyDowns.count(0x58); // X
	knifing = false;
	if (attacking) {
		if (currentTime - lastAttackTime >= ATTACK_COOLDOWN) {
			lastAttackTime = currentTime;
		}
		else {
			attacking = false;
		}
	}
	if (attacking) {
		for (size_t i = 0; i < soldiers.size(); i++) {
			if (IsOverlap(*this, soldiers[i])) {
				knifing = true;
			}
		}
	}
}

void Marco::move() {
	dx = 0;
	dy = 0;
	collideWithBullet();
	moveLeftRight();
	if (lookingUp && !pressingDown) {
		facingY = -1;
	}
	else if (!lookingUp && pressingDown) {
		facingY = 1;
	}
	else {
		facingY = 0;
	}
	collideWithWall();
	collideWithGround();
	jumpAndFall();
	attack();
	if (x + dx > 0&&720 > x + dx ) {
		x += dx;
	}
	y += dy;
}

void Marco::attack() {
	if (attacking) {
		addBullet(x + facingX * 20, y + 20, 20, facingX, facingY, "hero");
	}
}

void Marco::moveLeftRight() {
	if (movingLeft) {
		dx += -speedX;
		facingX = -1;
		flip = true;
	}
	if (movingRight&&(Checkcheckpoint()||!scroll)) {
		dx += speedX;
		facingX = 1;
		flip = false;
	}
}

void Marco::jumpAndFall() {
	if (jumping && !inAir) {
		velocityY = JUMP_VELOCITY;
		inAir = true;
	}
	else {
		velocityY += GRAVITY;
	}
	dy += velocityY;
}

void Marco::collideWithBullet() {

}

void Marco::updateAction() {

	/* action priority order by
	DIE,
	CROUCH_GRENADE,
	CROUCH_KNIFE,
	CROUCH_SHOOT_UP,
	CROUCH_SHOOT,
	GRENADE,
	KNIFE,
	SHOOT_UP,
	SHOOT_DOWN,
	SHOOT,
	LOOK_UP,
	JUMP,
	MOVE,
	IDLE
	*/
	
	lastAction = action;
	if (pressingDown) {
		if (inAir) {
			if (throwingGrenade) {
				action = Action::GRENADE;
			}
			else if (attacking) {
				if (nearEnemy) {
					action = Action::KNIFE;
				}
				else {
					action = Action::SHOOT_DOWN;
					once = false;
				}
			}
			else if (movingLeft || movingRight) {
				action = Action::JUMP;
			}
			else {
				action = Action::JUMP;
			}
		}
		else {
			if (throwingGrenade) {
				action = Action::CROUCH_GRENADE;
			}
			else if (attacking) {
				if (nearEnemy) {
					action = Action::CROUCH_KNIFE;
				}
				else {
					action = Action::CROUCH_SHOOT;
					once = false;
				}
			}
			else if (movingLeft || movingRight) {
				action = Action::CROUCH_MOVE;
			}
			else {
				action = Action::CROUCH_IDLE;
			}
		}
	}
	else if (lookingUp) {
		if (inAir) {
			if (throwingGrenade) {
				action = Action::GRENADE;
			}
			else if (attacking) {
				if (nearEnemy) {
					action = Action::KNIFE;
				}
				else {
					action = Action::SHOOT_UP;
					once = false;
				}
			}
			else if (movingLeft || movingRight) {
				action = Action::JUMP;
			}
			else {
				action = Action::LOOK_UP;
			}
		}
		else {
			if (throwingGrenade) {
				action = Action::GRENADE;
			}
			else if (attacking) {
				if (nearEnemy) {
					action = Action::KNIFE;
				}
				else {
					action = Action::SHOOT_UP;
					once = false;
				}
			}
			else if (movingLeft || movingRight) {
				action = Action::MOVE;
			}
			else {
				action = Action::LOOK_UP;
			}
		}
	}
	else {
		if (inAir) {
			if (throwingGrenade) {
				action = Action::GRENADE;
			}
			else if (attacking) {
				if (nearEnemy) {
					action = Action::KNIFE;
				}
				else {
					action = Action::SHOOT;
					once = false;
				}
			}
			else if (movingLeft || movingRight) {
				action = Action::JUMP;
			}
			else {
				action = Action::JUMP;
			}
		}
		else {
			if (throwingGrenade) {
				action = Action::GRENADE;
			}
			else if (attacking) {
				if (nearEnemy) {
					action = Action::KNIFE;
				}
				else {
					action = Action::SHOOT;
					once = false;
				}
			}
			else if (movingLeft || movingRight) {
				action = Action::MOVE;
			}
			else {
				if(once)
					action = Action::IDLE;
			}
		}
	}
	//lastAction = action;
	/*
	if (pressingDown && throwingGrenade) {
		action = Action::CROUCH_GRENADE;
	}
	else if (pressingDown && knifing) {
		action = Action::CROUCH_KNIFE;
	}
	else if (pressingDown && lookingUp && attacking) {
		action = Action::CROUCH_SHOOT_UP;
	}
	else if (pressingDown && attacking) {
		action = Action::CROUCH_SHOOT;
	}
	else if (throwingGrenade) {
		action = Action::GRENADE;
	}
	else if (knifing) {
		action = Action::KNIFE;
	}
	else if (lookingUp && attacking) {
		action = Action::SHOOT_UP;
	}
	else if (inAir && pressingDown && attacking) {
		action = Action::SHOOT_DOWN;
	}
	else if (attacking) {
		action = Action::SHOOT;
		once = false;
	}
	else if (lookingUp) {
		action = Action::LOOK_UP;
	}
	else if (inAir) {
		action = Action::JUMP;
	}
	else if (movingLeft || movingRight) {
		action = Action::MOVE;
	}
	else {
		if(once)
			action = Action::IDLE;
	}
	*/
}

void Marco::changeAnimation() {
	if (action != lastAction) {
		animationRange = animationRanges[static_cast<int>(action)];
		animationDelay = animationDelays[static_cast<int>(action)];
		SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
	}
}

void Marco::updateAnimation() {
	if (clock() - start > animationDelay) {
		SetFrameIndexOfBitmap(((GetFrameIndexOfBitmap()- animationRange.first- +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first))+ animationRange.first + ((flip) ? animationflipBias : 0));
		if ((GetFrameIndexOfBitmap() - animationRange.first- +((flip) ? animationflipBias : 0)) % (animationRange.second - animationRange.first ) == 0)
			once = true;
		start = clock();
	}
}

void Marco::collideWithGround() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1 && velocityY > 0) {
			//&& (this->GetTop() + this->GetHeight()) - Ground::GetX_Height(grounds[i], x) < 15;
			dy = Ground::GetX_Height(grounds[i], abs(ViewPointX) + x) - GetHeight() - y + ViewPointY - ViewPointYInit;
			
			if (abs(dy) > 40) // Prevent lifting by steep wall
				dy = 0;

			// Stop falling
			velocityY = 0;
			inAir = false;
		}
	}
}

void Marco::collideWithWall() {
	for (size_t i = 0; i < grounds.size(); i++) {
		bool t = Ground::isOnGroundLeft(*this, grounds[i]);
		if (t) {
			dx = 0;
		}
		if (dx >= 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			dx = 0;
		}
		else if (dx <= 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			dx = 0;
		}
	}
}

void Marco::draw() {
	if (alive&&!Driving) {
		SetTopLeft(x, y);
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}
void Marco::JumpOutDrving(int _x,int _y) {
	x = _x;
	y = _y;
	velocityY = JUMP_VELOCITY;
	inAir = true;
	dy += velocityY;
}
void Marco::dead()
{
	dying = true;
	deathTimer = clock();
}

bool Marco::isAttacking() {
	return attacking;
}
