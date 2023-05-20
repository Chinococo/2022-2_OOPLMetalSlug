#include "stdafx.h"
#include "../header/GameStorage.h"

Prisoner::Prisoner(int x, int y) : Character(x, y, velocityX) {
	this->x = x;
	this->y = y;
	anchoredX = x;
	anchoredY = y;
}


void Prisoner::update() {
	control();
}

void Prisoner::handleTied() {
	// Set sprite and action for this state
	sprite = Sprite::TIED;
	action = Action::TIED;

	// Switch to next action
	bool rescuredByHeroKnife = IsOverlap(*this, marco) && marco.isAttacking();
	bool rescuredByHeroBullet = false;

	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i].owner == "hero" && IsOverlap(*this, bullets[i])) {
			rescuredByHeroBullet = true;
			break;
		}
	}

	if (rescuredByHeroKnife || rescuredByHeroBullet) {
		sprite = Sprite::RESCUED;
		action = Action::RESCUED;
	}
}

void Prisoner::handleRescued() {
	// Set sprite and action for this state
	sprite = Sprite::RESCUED;
	action = Action::RESCUED;

	// Switch to next action
	if (isAnimationDone) {
		sprite = Sprite::MOVE;
		action = Action::MOVE;
	}
}

void Prisoner::handleMove() {
	// Set sprite and action for this state
	sprite = Sprite::MOVE;
	action = Action::MOVE;

	move();
	
	// Switch to next action
	if (IsOverlap(*this, marco)) {
		sprite = Sprite::REWARD;
		action = Action::REWARD;
	}
}

void Prisoner::handleReward() {
	// Set sprite and action for this state
	sprite = Sprite::REWARD;
	action = Action::REWARD;

	// Build a new pickup here (point pickup or weapon pickup)


	// Switch to next action
	if (isAnimationDone) {
		sprite = Sprite::MOVE;
		action = Action::LEAVE;
	}
}

void Prisoner::handleLeave() {
	// Set sprite and action for this state
	sprite = Sprite::MOVE;
	action = Action::LEAVE;

	alive = false; // Waiting to be deleted
}


void Prisoner::init() {
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "prisoner")
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

	/* filp */
	for (unsigned i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "prisoner")
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
	animationRange = animationRanges[static_cast<int>(sprite)];
	animationDelay = animationDelays[static_cast<int>(sprite)];
}

void Prisoner::control() {
	if (!alive) {
		return;
	}

	switch (action) {
	case Action::TIED:
		handleTied();
		break;
	case Action::RESCUED:
		handleRescued();
		break;
	case Action::MOVE:
		handleMove();
		break;
	case Action::REWARD:
		handleReward();
		break;
	case Action::LEAVE:
		handleLeave();
		break;
	}

	SetTopLeft(x + ViewPointX, y - ViewPointY + ViewPointYInit);

	// Handle animation
	updateAction();
	changeAnimation();
	updateAnimation();
}

void Prisoner::move() {
	dx = 0;
	dy = 0;

	// Horizontal movement
	moveLeftRight();
	collideWithWall();

	// Vertical movement
	collideWithGround();
	jumpAndFall();

	collideWithBorder();

	x += dx;
	y += dy;
}

void Prisoner::moveLeftRight() {
	if (direction == "left") {
		dx -= velocityX;
		facingX = -1;
		flip = false;
		
		if (abs(x + dx - anchoredX) > WANDER_RANGE) {
			// too far away from anchoredX, turn back
			direction = "right";
		}
	}
	else if (direction == "right") {
		dx += velocityX;
		facingX = 1;
		flip = true;

		if (abs(x + dx - anchoredX) > WANDER_RANGE) {
			// too far away from anchoredX, turn back
			direction = "left";
		}
	}
}

void Prisoner::jumpAndFall() {
	velocityY += (inAir) ? GRAVITY : 0;
	dy += velocityY;
}

void Prisoner::changeAnimation() {
	animationRange = animationRanges[static_cast<int>(sprite)];
	animationDelay = animationDelays[static_cast<int>(sprite)];
	SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
}

void Prisoner::updateAnimation() {
	if (clock() - start > animationDelay) {
		SetFrameIndexOfBitmap(((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0) + 1) % (animationRange.second - animationRange.first)) + animationRange.first + ((flip) ? animationflipBias : 0));
		if ((GetFrameIndexOfBitmap() - animationRange.first - +((flip) ? animationflipBias : 0)) % (animationRange.second - animationRange.first) == 0)
			once = true;
		start = clock();
	}

	/* Modified but untested code
	if (clock() - start > animationDelay) {
		int frameIndex = GetFrameIndexOfBitmap();
		int animationBias = (flip) ? animationflipBias : 0;
		int totalFrames = animationRange.second - animationRange.first;
		int newFrameIndex = (frameIndex - animationRange.first - animationBias + 1) % totalFrames;
		int frameOffset = newFrameIndex + animationRange.first + animationBias;
		SetFrameIndexOfBitmap(frameOffset);

		bool isLastFrame = (frameOffset - animationRange.first) % totalFrames == 0;
		once = isLastFrame;

		start = clock();
	}
	*/
}

void Prisoner::collideWithGround() {
	// Check for falling
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1 && velocityY > 0) {
			dy = Ground::GetX_Height(grounds[i], abs(ViewPointX) + x) - GetHeight() - y + ViewPointY - ViewPointYInit;

			if (abs(dy) > 40) // Prevent lifting by steep wall
				dy = 0;

			// Stop falling
			inAir = false;
			velocityY = 0;

			sprite = Sprite::FALL;
			break;
		}
	}
}

void Prisoner::collideWithWall() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (dx > 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			dx = 0;
		}
		else if (dx < 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			dx = 0;
		}
	}
}

void Prisoner::collideWithBorder() {
	if (x + dx < 0) {
		dx = -x;
	}
	else if (x + dx > 800) {
		dx = 800 - x;
	}

	if (y + dy < 0) {
		dy = -y;
	}
	else if (y + dy > 600) {
		dy = 600 - y;
	}
}

void Prisoner::draw() {
	if (alive) {
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

void Prisoner::updateAction() {
	// Pattern changed, no need for this method
}
