#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Soldier::Soldier(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {

}

void Soldier::init() {
	std::vector<std::string> paths;

	int delay = 300;
	std::pair<int, int> range = { 0, 6 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/idle/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 70;
	range = { 6, 18 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/move/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 300;
	range = { 18, 28 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/jump/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 300;
	range = { 28, 37 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/bomb/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 300;
	range = { 37, 43 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/die/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);
	animationflipBias = range.second;



	/* flip */

	range = { 0, 6 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/idle/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 6, 18 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/move/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 18, 28 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/jump/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 28, 37 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/bomb/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 37, 46 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img_v2/soldier/die/flip_" + std::to_string(i) + ".bmp");
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
	if (distanceX > 0) {
		movingRight = true;
		movingLeft = false;
	}
	else if (distanceX < 0) {
		movingLeft = true;
		movingRight = false;
	}

	if ((currentTime - lastJumpTime >= JUMP_COOLDOWN) && (rand() % 10 == 0)) {
		lastJumpTime = currentTime;
		jumping = true;
	}
	else {
		jumping = false;
	}

	
	if ((currentTime - lastAttackTime >= ATTACK_COOLDOWN) && abs(distanceX) < 200 ) {
		lastAttackTime = currentTime;
		attacking = true;
	}
	else {
		attacking = false;
	}
	
}

void Soldier::move() {
	dx = 0;
	dy = 0;
	collideWithBullet();
	collideWithWall();
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
		addBullet(ViewPointX+x + facingX * 20, y + 20, 20, facingX, facingY, "enemy");
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

void Soldier::collideWithBullet() {
	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i].owner == "hero" && IsOverlap(*this, bullets[i])) {
			dying = true;
			deathTimer = clock();
		}
	}
}

void Soldier::updateAction() {
	lastAction = action;
	if (inAir) {
		if (attacking) {
			action = Action::BOMB;
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
		start = clock();
	}
}

void Soldier::collideWithGround() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			dy = Ground::GetX_Height(grounds[i], x) - GetHeight() - y;
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
