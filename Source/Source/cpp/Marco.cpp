#include "stdafx.h"
#include <chrono>
#include "../header/GameStorage.h"

using namespace game_framework;

Marco::Marco(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {

}

void Marco::init() {
	// order following enum class Action
	// IDLE, MOVE, JUMP, LOOK_UP, SHOOT, SHOOT_UP, SHOOT_DOWN, KNIFE, GRENADE, CROUCH_SHOOT, CROUCH_SHOOT_UP, CROUCH_KNIFE, CROUCH_GRENADE, DIE
	
	std::vector<std::string> paths;
	
	int delay = 300;
	std::pair<int, int> range = { 0, 4 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/idle/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 100;
	range = { 4, 27 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/move/" + std::to_string(i) + ".bmp");
	}
	range = { 4, 16 };
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 1000;
	range = { 27, 33 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/jump/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 1000;
	range = { 33, 41 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/lookUp/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 30;
	range = { 41, 49 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/shoot/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	// no image now
	delay = 300;
	range = { 49, 53 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/shootUp/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	// no image now
	delay = 300;
	range = { 53, 57 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/shootDown/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 300;
	range = { 57, 65 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/knife/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	// no image now
	delay = 300;
	range = { 65, 69 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/grenade/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 300;
	range = { 69, 86 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/crouchShoot/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	// no image now
	delay = 300;
	range = { 86, 90 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/crouchShootUp/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	// no image now
	delay = 300;
	range = { 90, 94 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/crouchKnife/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 300;
	range = { 94, 106 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/crouchGrenade/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);

	delay = 1000;
	range = { 106, 108 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/die/" + std::to_string(i) + ".bmp");
	}
	animationRanges.push_back(range);
	animationDelays.push_back(delay);
	animationflipBias = range.second;



	/*filp*/

	range = { 0, 4 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/idle/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 4, 27 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/move/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 27, 33 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/jump/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 33, 41 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/lookUp/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 41, 49 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/shoot/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 49, 53 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/shootUp/" + std::to_string(i) + ".bmp");
	}
	range = { 53, 57 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/shootDown/" + std::to_string(i) + ".bmp");
	}
	range = { 57, 65 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/knife/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 65, 69 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/grenade/" + std::to_string(i) + ".bmp");
	}

	range = { 69, 86 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/crouchShoot/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 86, 90 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/crouchShootUp/" + std::to_string(i) + ".bmp");
	}
	range = { 90, 94 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/noImg/crouchKnife/" + std::to_string(i) + ".bmp");
	}
	range = { 94, 106 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/crouchGrenade/flip_" + std::to_string(i) + ".bmp");
	}
	range = { 106, 108 };
	for (int i = 0; i < range.second - range.first; i++) {
		paths.push_back("resources/img/hero/marco/die/flip_" + std::to_string(i) + ".bmp");
	}


	LoadBitmapByString(paths, RGB(0, 0, 0));
	animationRange = animationRanges[static_cast<int>(action)];
	animationDelay = animationDelays[static_cast<int>(action)];
}

void Marco::update() {
	if (alive) {
		control();
		move();
		updateAction();
		changeAnimation();
		updateAnimation();
	}
	else {
		die();
	}
}

void Marco::control() {
	clock_t currentTime = clock();
	scroll = (this->GetLeft() > 400);
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
	collideWithWall();
	collideWithGround();
	jumpAndFall();
	attack();
	if(x + dx>0)
		x += dx;
	y += dy;
}

void Marco::attack() {
	if (attacking) {
		addBullet(x+(flip?-1:1)*20, y+20, 20, facingX, facingY, "hero");
	}
}

void Marco::moveLeftRight() {
	if (movingLeft) {
		dx += -speedX;
		facingX = -1;
		flip = true;
	}
	if (movingRight&&!scroll) {
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
	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i].owner == "enemy" && IsOverlap(*this, bullets[i])) {
			alive = false;
		}
	}
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
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			dy = Ground::GetX_Height(grounds[i], x) - GetHeight() - y;
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

void Marco::die() {
	animationRange = animationRanges[static_cast<int>(Action::DIE)];
}

void Marco::draw() {
	if (alive) {
		SetTopLeft(x, y);
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}
