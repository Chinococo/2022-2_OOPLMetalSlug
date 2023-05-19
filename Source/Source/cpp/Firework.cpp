#include "stdafx.h"
#include "../header/GameStorage.h"

Firework::Firework(int x, int y, std::string direction) : Character(x, y, velocityX) {
	this->direction = direction;
	dying = false;
	alive = true;
}

void Firework::init() {
	/*
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");

	std::pair<int, int> range;
	std::vector<std::string> paths;

	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "firework")
			continue;

		std::string prefix = csv[i][2];
		int delay = std::stoi(csv[i][3]);
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };

		animationRanges.push_back(range);
		animationDelays.push_back(delay);

		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + std::to_string(i) + ".bmp");
		}
	}

	animationflipBias = range.second;

	// filp
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "firework")
			continue;

		string prefix = csv[i][2];
		int delay = std::stoi(csv[i][3]);
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };

		animationRanges.push_back(range);
		animationDelays.push_back(delay);

		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + "flip_" + std::to_string(i) + ".bmp");
		}
	}

	LoadBitmapByString(paths, RGB(0, 0, 0));
	//animationRange = animationRanges[static_cast<int>(action)];
	//animationDelay = animationDelays[static_cast<int>(action)];
	*/

	if (direction == "left") {
		LoadBitmapByString({ "resources/img_v2/firework/move/0.bmp" }, RGB(0, 0, 0));
	}
	else if (direction == "right") {
		LoadBitmapByString({ "resources/img_v2/firework/move/flip_0.bmp" }, RGB(0, 0, 0));
	}
}

void Firework::update() {
	if (!dying) {
		move();
		int x1 = x - abs(ViewPointX);
		int y1 = y - ViewPointY + ViewPointYInit;
		SetTopLeft(x-abs(ViewPointX), y-ViewPointY+ViewPointYInit);
		return;
	}
	if (clock() - deathTimer >= ALIVE_DURATION) {
		alive = false;
		return;
	}
	/*
	// Animation
	updateAction();
	changeAnimation();
	updateAnimation();
	*/
}

void Firework::control() {
	
}

void Firework::move() {
	dx = 0;
	dy = 0;

	collideWithHero();
	moveLeftRight();
	collideWithGround();

	x += dx;
	y += dy;
}

void Firework::moveLeftRight() {
	if (direction == "left") {
		dx = -velocityX;
	}
	else if (direction == "right") {
		dx = velocityX;
	}
}

void Firework::jumpAndFall() {

}

void Firework::updateAction() {
	if (dying) {
		action = Action::DIE;
		return;
	}
	action = Action::MOVE;
}

void Firework::changeAnimation() {
	if (action != lastAction) {
		animationRange = animationRanges[static_cast<int>(action)];
		animationDelay = animationDelays[static_cast<int>(action)];
		SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
	}
}

void Firework::updateAnimation() {
	if (clock() - start > animationDelay) {
		SetFrameIndexOfBitmap(((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first)) + animationRange.first + ((flip) ? animationflipBias : 0));
		start = clock();
	}
}

void Firework::collideWithGround() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			dy = Ground::GetX_Height(grounds[i], x) - GetHeight() - y + ViewPointY - ViewPointYInit;
			if (abs(dy) > 40) {
				dy = 0;
			}
			return;
		}
	}
}

void Firework::collideWithWall() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			dying = true;
			deathTimer = clock();
			return;
		}
		else if (Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			dying = true;
			deathTimer = clock();
			return;
		}
	}
}

void Firework::collideWithHero() {
	if (IsOverlap(*this, marco)) {
		dying = true;
		deathTimer = clock();
	}
}

void Firework::draw() {
	if (!alive) {
		UnshowBitmap();
		return;
	}
	ShowBitmap(0.8);
}
