#include "stdafx.h"
#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Enemy_tank::Enemy_tank(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {
	init();
}

void Enemy_tank::init() {
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "enemy_tank")
			continue;
		int delay = std::stoi(csv[i][3]);
		string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };
		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + std::to_string(i) + ".bmp");
		}
		animationRanges.push_back(range);
		animationDelays.push_back(delay);
	}
	animationflipBias = range.second;

	/*filp*/
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "enemy_tank")
			continue;
		int delay = std::stoi(csv[i][3]);
		string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };
		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + "flip_" + std::to_string(i) + ".bmp");
		}
		animationRanges.push_back(range);
		animationDelays.push_back(delay);
	}
	LoadBitmapByString(paths, RGB(255, 255, 255));
	animationRange = animationRanges[static_cast<int>(action)];
	animationDelay = animationDelays[static_cast<int>(action)];
}

void Enemy_tank::update() {
	if (!dying) {
		control();
		move();
		updateAction();
		changeAnimation();
		updateAnimation();
	}
	else {
		action = Action::DIE;
		changeAnimation();
		updateAnimation();
		if (clock() - deathTimer > 1000) {
			alive = false;
		}
	}
}

void Enemy_tank::control() { // AI
	if (!marco.isAlive()) {
		movingLeft = false;
		movingRight = false;
		jumping = false;
		lookingUp = false;
		attacking = false;
		throwingGrenade = false;
		pressingDown = false;
		return;
	}

	clock_t currentTime = clock();

	int distanceX = (abs(ViewPointX) + marco.GetLeft()) - x;

	movingLeft = false;
	movingRight = false;
	if ( abs(distanceX) < 700) {
		if (distanceX > 0) {
			movingRight = true;
		}
		else if (distanceX < 0) {
			movingLeft = true;
		}
	}


	if (currentTime - lastAttackTime >= ((state == "map1") ? ATTACK_COOLDOWN : ATTACK_COOLDOWN / 2) && abs(distanceX) < 400) {
		lastAttackTime = currentTime;
		attacking = true;
	}
	else {
		attacking = false;
	}

}

void Enemy_tank::move() {
	dx = 0;
	dy = 0;
	collideWithBullet();
	moveLeftRight();
	collideWithWall();
	if (lookingUp && !pressingDown) {
		facingY = -1;
	}
	else if (!lookingUp && pressingDown) {
		facingY = 1;
	}
	else {
		facingY = 0;
	}
	collideWithGround();
	jumpAndFall();
	attack();
	if (x + dx > 0) {
		x += dx;
	}
	y += dy;
}

void Enemy_tank::attack() {
	if (attacking) {
		//addBullet(ViewPointX+x + facingX * 20, y + 20, 20, facingX, facingY, "enemy");
		std::string direction = (facingX == -1) ? "left" : "right";
		if(direction=="left")
			enemy_tnak_bullets.push_back(Enemy_tank_bullet(ViewPointX + x - 5, y + 20,direction));
		else
			enemy_tnak_bullets.push_back(Enemy_tank_bullet(ViewPointX + x +5+GetWidth(), y + 20, direction));
	}
}

void Enemy_tank::moveLeftRight() {
	int distanceX = abs((abs(ViewPointX) + marco.GetLeft()) - x);
	if (movingLeft) {
		if(distanceX>100)
			dx += -speedX;
		facingX = -1;
		flip = false;
	}
	if (movingRight) {
		if (distanceX > 100)
			dx += speedX;
		facingX = 1;
		flip = true;
	}
}

void Enemy_tank::jumpAndFall() {
	if (jumping && !inAir) {
		velocityY = JUMP_VELOCITY;
		inAir = true;
	}
	else {
		velocityY += GRAVITY;
	}
	dy += velocityY;
}

void Enemy_tank::dead() {
	if (!dying) {
		dying = true;
		deathTimer = clock();
	}
}

void Enemy_tank::collideWithBullet()
{
}

void Enemy_tank::updateAction() {
	lastAction = action;
	if (inAir) {
		if (attacking) {
			action = Action::Shooting;
			once = false;
		}
	}
	else {
		if (attacking) {
			action = Action::Shooting;
			once = false;
		}
		else if (movingLeft || movingRight) {
			action = Action::MOVE;
		}
		else {
			action = Action::IDLE;
		}
	}
}

void Enemy_tank::changeAnimation() {
	if (action != lastAction) {
		animationRange = animationRanges[static_cast<int>(action)];
		animationDelay = animationDelays[static_cast<int>(action)];
		SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
	}
}

void Enemy_tank::updateAnimation() {
	if (clock() - start > animationDelay) {
		SetFrameIndexOfBitmap(((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first)) + animationRange.first + ((flip) ? animationflipBias : 0));
		if ((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0)) % (animationRange.second - animationRange.first) == 0)
			once = true;
		start = clock();
	}
}

void Enemy_tank::collideWithGround() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			dy = Ground::GetX_Height(grounds[i], x) - GetHeight() - y + ViewPointY - ViewPointYInit;
			velocityY = 0;
			inAir = false;
		}
	}
}

void Enemy_tank::collideWithWall() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (dx > 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			dx = 0;
		}
		else if (dx < 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			dx = 0;
		}
	}
}

void Enemy_tank::draw() {
	if (alive) {
		SetTopLeft(ViewPointX + x, y);
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

ColBox Enemy_tank::getColBox(void) {
	return {
		{x, y},
		{x + GetWidth(), y + GetHeight()}
	};
}

void Enemy_tank::reset(void) {
	once = true;
	velocityY = 0;
	movingLeft = false;
	movingRight = false;
	jumping = false;
	inAir = false;
	lookingUp = false;
	attacking = false;
	nearEnemy = false;
	throwingGrenade = false;
	pressingDown = false;
	lastJumpTime = clock();
	lastAttackTime = clock();
	action = Action::IDLE;
	lastAction = Action::IDLE;
	alive = true;
	dying = false;
	x = 100;
	y = 300;
	dx = 0;
	dy = 0;
	facingX = 1;
	facingY = 0;
	flip = false;
	deathTimer = clock();
	start = clock();
	SetFrameIndexOfBitmap(0);
}
