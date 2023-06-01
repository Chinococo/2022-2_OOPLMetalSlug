#include "stdafx.h"
#include <chrono>
#include "../header/GameStorage.h"

using namespace game_framework;

tank::tank(int _x, int _y, int _speedX) : Character(_x, _y, _speedX) {
	barrel = new tank_barrel(x+20, y+20);
}

void tank::init() {
	barrel->init();
	// order following enum class Action
	// IDLE, MOVE, JUMP, LOOK_UP, SHOOT, SHOOT_UP, SHOOT_DOWN, KNIFE, GRENADE, CROUCH_SHOOT, CROUCH_SHOOT_UP, CROUCH_KNIFE, CROUCH_GRENADE, DIE
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "tank")
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
		if (csv[i][0] != "tank")
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

void tank::update() {
	if (!dying) {
		control();
		move();
		updateAction();
		barrel->update(x,y);
		changeAnimation();
		updateAnimation();
	}
	else {
		Driving = false;
		//action = Action::DIE;
		changeAnimation();
		updateAnimation();
		if (clock() - deathTimer > 1000) {
			alive = false;
		}
	}
}

void tank::control() {
	clock_t currentTime = clock();
	if (Driving) {
		scroll = (this->GetLeft() > 400);
	}
	out = keyDowns.count(0x43); // C
	if (Driving) {
		movingLeft = keyDowns.count(VK_LEFT);
		movingRight = keyDowns.count(VK_RIGHT);
		jumping = keyDowns.count(VK_SPACE);
		lookingUp = keyDowns.count(VK_UP);
		pressingDown = keyDowns.count(VK_DOWN);
		attacking = keyDowns.count(0x5A); // Z
		throwingGrenade = keyDowns.count(0x58); // X
		
	}
	
	knifing = false;
	if (attacking) {
		if (currentTime - lastAttackTime >= ATTACK_COOLDOWN) {
			lastAttackTime = currentTime;
		}
		else {
			attacking = false;
		}
	}
}

void tank::move() {
	dx = 0;
	dy = 0;
	collideWithGround();
	jumpAndFall();
	take_in();
	take_out();
	if (Driving) {
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
		attack();
		if (x + dx > 0&&this->GetLeft()+this->GetWidth()<800) {
			x += dx;
		}
		y += dy;
	}else
		y += dy;
}

void tank::attack() {
	if (attacking) {
		tank_bullet * _bullet = new tank_bullet(x,y);
		_bullet->init();
		tank_bullets.push_back(_bullet);
	}
}
void tank::increaseX(int increse) {
	x += increse;
}
void tank::moveLeftRight() {
	if (movingLeft) {
		dx += -speedX;
		if (barrel->GetAngele() != 26&&clock()- roate>100) {
			roate = clock();
			if (barrel->GetAngele() >= 11 && barrel->GetAngele() <= 25)
				barrel->SetAngele((barrel->GetAngele()+1)%32);
			else
				barrel->SetAngele((barrel->GetAngele() + 31) % 32);
		}
		facingX = -1;
		flip = true;
	}
	if (movingRight ) {
		if (barrel->GetAngele() != 10 && clock() - roate > 100) {
			roate = clock();
			int t = barrel->GetAngele();
			if (barrel->GetAngele() >= 11 && barrel->GetAngele() <= 25)
				barrel->SetAngele((barrel->GetAngele() + 31) % 32);
			else
				barrel->SetAngele((barrel->GetAngele() + 1) % 32);
		}
		if ((Checkcheckpoint() || !scroll)) {
			dx += speedX;
			facingX = 1;
			flip = false;
		}
	}
}

void tank::jumpAndFall() {
	if (jumping && !inAir) {
		velocityY = JUMP_VELOCITY;
		inAir = true;
	}
	else {
		velocityY += GRAVITY;
	}
	dy += velocityY;
}

void tank::collideWithBullet() {
	for (size_t i = 0; i < soldierFireworks.size(); i++) {
		if (IsOverlap(*this, soldierFireworks[i])) {
			dying = true;
			deathTimer = clock();
			break;
		}
	}
	for (size_t i = 0; i < rshobus.size(); i++) {
		if (rshobus[i].isHurt(*this)) {
			dying = true;
			deathTimer = clock();
			break;
		}
	}
}

void tank::updateAction() {
	lastAction = action;
	if (inAir) {
		action = Action::JUMP;
	}
	else if(pressingDown|| movingLeft || movingRight|| throwingGrenade){
		if (pressingDown) {
			if (movingLeft || movingRight)
				action = Action::Crouch_Driving;
			else
				action = Action::Crouch;
		}
		else if (movingLeft || movingRight) {
			action = Action::MOVING;
		}
		else if (throwingGrenade) {
			action = Action::SOOTING;
			once = false;
		}
	}else if(once){
		action = Action::IDLE;
	}
	
}

void tank::changeAnimation() {
	if (action != lastAction) {
		animationRange = animationRanges[static_cast<int>(action)];
		animationDelay = animationDelays[static_cast<int>(action)];
		SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
	}
}

void tank::updateAnimation() {
	if (clock() - start > animationDelay) {
		SetFrameIndexOfBitmap(((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first)) + animationRange.first + ((flip) ? animationflipBias : 0));
		if ((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0)) % (animationRange.second - animationRange.first) == 0)
			once = true;
		start = clock();
	}
}

void tank::collideWithGround() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1 && velocityY > 0) {
			//&& (this->GetTop() + this->GetHeight()) - Ground::GetX_Height(grounds[i], x) < 15;
			if(dy==0||abs(dy)<abs( Ground::GetX_Height(grounds[i], x) - GetHeight() - y + ViewPointY - ViewPointYInit))
				dy = Ground::GetX_Height(grounds[i], x) - GetHeight() - y + ViewPointY - ViewPointYInit;
			// Stop falling
			velocityY = 0;
			inAir = false;
		}
	}
}

void tank::collideWithWall() {
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

void tank::draw() {
	for (unsigned i = 0; i < bullets.size(); i++)
		bullets[i].update();
	if (alive) {
		if (drving==true) {
			SetTopLeft(ViewPointX + x, y - ViewPointYInit + ViewPointY);
		}
		else {
			SetTopLeft(ViewPointX + x, y - ViewPointYInit + ViewPointY);
		}
		ShowBitmap();
		barrel->draw();

		
	}
	else {
		UnshowBitmap();
	}
}

void tank::take_in()
{
	clock_t temp = clock() - out_drviing;
	if (IsOverlap(marco, *this) && (marco.GetTop() + marco.GetHeight() - 30) <= this->GetTop() && clock() - out_drviing > 1000) {
		Driving = true;
		in_driving = clock();
		//x = x + ViewPointX;
		//y = y + ViewPointYInit - ViewPointY;
		//SetTopLeft(x, y);
	}
}

void tank::take_out()
{
	if (Driving && out && clock() - in_driving > 1000) {
		Driving = false;
		marco.JumpOutDrving(ViewPointX + x - 80, y - ViewPointYInit + ViewPointY);
		out_drviing = clock();
	}
}

void tank::dead()
{
	dying = true;
	deathTimer = clock();
}

bool tank::isAttacking() {
	return attacking;
}
