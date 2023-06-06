#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Soldier::Soldier(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {
	
}

void Soldier::init() {
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "soldier")
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
		if (csv[i][0] != "soldier")
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
	LoadBitmapByString(paths, RGB(0, 0, 0));
	animationRange = animationRanges[static_cast<int>(action)];
	animationDelay = animationDelays[static_cast<int>(action)];
}

void Soldier::update() {
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

void Soldier::control() { // AI
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
	if (abs(distanceX) > 250) {
		if (distanceX > 0) {
			movingRight = true;
		}
		else if (distanceX < 0) {
			movingLeft = true;
		}
	}

	/*
	if ((currentTime - lastJumpTime >= JUMP_COOLDOWN) && (rand() % 10 == 0)) {
		lastJumpTime = currentTime;
		jumping = true;
	}
	else {
		jumping = false;
	}
	*/

	/*
	if (currentTime - lastAttackTime >= ATTACK_COOLDOWN) {
		lastAttackTime = currentTime;
		attacking = true;
	}
	else {
		attacking = false;
	}
	*/
}

void Soldier::move() {
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

void Soldier::attack() {
	if (attacking) {
		//addBullet(ViewPointX+x + facingX * 20, y + 20, 20, facingX, facingY, "enemy");
		std::string direction = (facingX == -1) ? "left" : "right";
		addFirework(x, y , direction);
	}
}

void Soldier::moveLeftRight() {
	if (movingLeft) {
		dx += -speedX;
		facingX = -1;
		flip = false;
	}
	if (movingRight) {
		dx += speedX;
		facingX = 1;
		flip = true;
	}
}

void Soldier::jumpAndFall() {
	if (jumping && !inAir) {
		velocityY = JUMP_VELOCITY;
		inAir = true;
	}
	else {
		velocityY += GRAVITY;
	}
	dy += velocityY;
}

void Soldier::dead() {
	if (!dying) {
		dying = true;
		deathTimer = clock();
	}
}

void Soldier::collideWithBullet()
{
}

void Soldier::updateAction() {
	lastAction = action;
	if (inAir) {
		if (attacking) {
			action = Action::BOMB;
			once = false;
		}
		else if (movingLeft || movingRight) {
			action = Action::JUMP;
		}
		else {
			action = Action::JUMP;
		}
	}
	else {
		if (attacking) {
			action = Action::BOMB;
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

void Soldier::changeAnimation() {
	if (action != lastAction) {
		animationRange = animationRanges[static_cast<int>(action)];
		animationDelay = animationDelays[static_cast<int>(action)];
		SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
	}
}

void Soldier::updateAnimation() {
	if (clock() - start > animationDelay) {
		SetFrameIndexOfBitmap(((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first)) + animationRange.first + ((flip) ? animationflipBias : 0));
		if ((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0)) % (animationRange.second - animationRange.first) == 0)
			once = true;
		start = clock();
	}
}

void Soldier::collideWithGround() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			dy = Ground::GetX_Height(grounds[i], x) - GetHeight() - y + ViewPointY - ViewPointYInit;
			velocityY = 0;
			inAir = false;
		}
	}
}

void Soldier::collideWithWall() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (dx > 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			dx = 0;
		}
		else if (dx < 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			dx = 0;
		}
	}
}

void Soldier::draw() {
	if (alive) {
		SetTopLeft(ViewPointX + x, y);
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

Soldier &Soldier::operator=(const Soldier &other) {
	x = other.x;
	y = other.y;
	speedX = other.speedX;
	return *this;
}

ColBox Soldier::getColBox(void) {
	return { {x, y}, {x + GetWidth(), y + GetHeight()} };
}
