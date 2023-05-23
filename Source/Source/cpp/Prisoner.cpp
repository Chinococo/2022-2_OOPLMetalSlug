#include "stdafx.h"
#include "../header/GameStorage.h"

Prisoner::Prisoner(int left, int top)
	: Character(left, top, velocityHorizontal),
	absoluteAnchorHorizontal(left) {}

void Prisoner::init() {
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;

	for (size_t i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "prisoner")
			continue;

		int delay = std::stoi(csv[i][3]);
		std::string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };

		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + std::to_string(i) + ".bmp");
		}

		animationRanges.push_back(range);
		animationDelays.push_back(delay);
	}

	animationflipBias = range.second;

	// filp
	for (size_t i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "prisoner")
			continue;

		int delay = std::stoi(csv[i][3]);
		std::string prefix = csv[i][2];
		range = { std::stoi(csv[i][1].substr(0, csv[i][1].find('~'))), std::stoi(csv[i][1].substr(csv[i][1].find('~') + 1)) };

		for (int i = 0; i < range.second - range.first; i++) {
			paths.push_back(prefix + "flip_" + std::to_string(i) + ".bmp");
		}

		animationRanges.push_back(range);
		animationDelays.push_back(delay);
	}

	LoadBitmapByString(paths, RGB(0, 0, 0));
	/*
	animationRange = animationRanges[static_cast<int>(currentSprite)];
	animationDelay = animationDelays[static_cast<int>(currentSprite)];
	*/
}

void Prisoner::update() {
	if (!alive) {
		return;
	}

	distanceHorizontal = 0;
	distanceVertical = 0;

	switch (currentAction) {
	case Action::TIED:
		handleActionTied();
		break;
	case Action::RESCUED:
		handleActionRescued();
		break;
	case Action::MOVE:
		handleActionMove();
		break;
	case Action::REWARD:
		handleActionReward();
		break;
	case Action::LEAVE:
		handleActionLeave();
		break;
	}

	absolutePositionLeft += distanceHorizontal;
	absolutePositionTop += distanceVertical;

	int relativePositionLeft = absolutePositionLeft + ViewPointX;
	int relativePositionTop = absolutePositionTop - ViewPointY + ViewPointYInit;

	SetTopLeft(relativePositionLeft, relativePositionTop);

	// Handle animation
	switchSprite(currentSprite);
	nextFrame();
}

void Prisoner::draw() {
	if (alive) {
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

void Prisoner::handleActionTied() {
	// Set sprite and action for this state
	currentSprite = Sprite::TIED;
	currentAction = Action::TIED;

	// Perform movement
	moveVertically(Direction::DOWN);

	// Handle Collision
	handleGroundCollision();

	// Switch to next action
	bool isRescuredByHeroKnife = IsOverlap(*this, marco) && marco.isAttacking();
	bool isRescuredByHeroBullet = false;

	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i].owner == "hero" && IsOverlap(*this, bullets[i])) {
			isRescuredByHeroBullet = true;
			break;
		}
	}

	if (isRescuredByHeroKnife || isRescuredByHeroBullet) {
		currentSprite = Sprite::RESCUED;
		currentAction = Action::RESCUED;
	}
}

void Prisoner::handleActionRescued() {
	// Set sprite and action for this state
	currentSprite = Sprite::RESCUED;
	currentAction = Action::RESCUED;

	// Perform movement
	moveVertically(Direction::DOWN);

	// Handle Collision
	handleGroundCollision();

	// Switch to next action
	if (animationDone) {
		currentSprite = Sprite::MOVE;
		currentAction = Action::MOVE;
	}
}

void Prisoner::handleActionMove() {
	// Set sprite and action for this state
	currentSprite = Sprite::MOVE;
	currentAction = Action::MOVE;

	// Perform movement
	int newPositionHorizontal = absolutePositionLeft + distanceHorizontal;
	int distanceFromAnchorHorizontal = abs(newPositionHorizontal - absoluteAnchorHorizontal);

	// Set direction
	if (distanceFromAnchorHorizontal > WANDER_DISTANCE) {
		if (currentDirectionHorizontal == Direction::LEFT) {
			currentDirectionHorizontal = Direction::RIGHT;
		}
		else if (currentDirectionHorizontal == Direction::RIGHT) {
			currentDirectionHorizontal = Direction::LEFT;
		}
	}

	moveHorizontally(currentDirectionHorizontal);
	moveVertically(Direction::DOWN);

	// Handle Collision
	handleWallCollision();
	handleGroundCollision();

	// Switch to next action
	if (isCollideWith(marco)) {
		currentSprite = Sprite::REWARD;
		currentAction = Action::REWARD;
	}
}

void Prisoner::handleActionReward() {
	// Set sprite and action for this state
	currentSprite = Sprite::REWARD;
	currentAction = Action::REWARD;

	// Perform movement
	moveVertically(Direction::DOWN);

	// Handle Collision
	collideWithGround();

	// Build a new pickup here (point pickup or weapon pickup)


	// Switch to next action
	if (animationDone) {
		currentSprite = Sprite::MOVE;
		currentAction = Action::LEAVE;
	}
}

void Prisoner::handleActionLeave() {
	// Set sprite and action for this state
	currentSprite = Sprite::MOVE;
	currentAction = Action::LEAVE;

	// Set direction
	currentDirectionHorizontal = Direction::LEFT;

	// Perform movement
	moveHorizontally(Direction::LEFT);
	moveVertically(Direction::DOWN);

	// Handle Collision
	handleWallCollision();
	handleGroundCollision();

	int relativePositionRight = absolutePositionLeft + ViewPointX + GetWidth();

	if (relativePositionRight < 0) {
		alive = false; // Waiting to be deleted
	}
}

void Prisoner::moveHorizontally(Direction direction) {
	if (direction == Direction::LEFT) {
		distanceHorizontal -= velocityHorizontal;
	}
	else if (direction == Direction::RIGHT) {
		distanceHorizontal += velocityHorizontal;
	}
}

void Prisoner::moveVertically(Direction direction) {
	if (direction == Direction::DOWN) {
		velocityVertical += GRAVITY;
		distanceVertical += velocityVertical;
	}
}

bool Prisoner::isCollideWith(Marco marco) {
	marco.GetLeft();
}

bool Prisoner::isCollideWith(Bullet bullet) {

}

void Prisoner::handleGroundCollision() {

}

void Prisoner::handleWallCollision() {

}

void Prisoner::handleBorderCollision() {

}

void Prisoner::switchSprite(Sprite sprite) {

}

void Prisoner::nextFrame() {

}

std::string Prisoner::getSprite() const {
	switch (currentSprite) {
	case Prisoner::Sprite::TIED:
		return "TIED";
	case Prisoner::Sprite::RESCUED:
		return "RESCUED";
	case Prisoner::Sprite::MOVE:
		return "MOVE";
	case Prisoner::Sprite::FALL:
		return "FALL";
	case Prisoner::Sprite::REWARD:
		return "REWARD";
	default:
		return "NONE";
	}
}

std::string Prisoner::getAction() const {
	switch (currentAction) {
	case Prisoner::Action::TIED:
		return "TIED";
	case Prisoner::Action::RESCUED:
		return "RESCUED";
	case Prisoner::Action::MOVE:
		return "MOVE";
	case Prisoner::Action::REWARD:
		return "REWARD";
	case Prisoner::Action::LEAVE:
		return "LEAVE";
	default:
		return "NONE";
	}
}

/*
void Prisoner::moveLeftRight() {
	if (direction == Direction::LEFT) {
		dx -= velocityX;
	}
	else if (direction == Direction::RIGHT) {
		dx += velocityX;
	}
	else {
		dx = 0;
	}
}

void Prisoner::fall() {
	velocityY += GRAVITY;
	dy += velocityY;
}

void Prisoner::collideWithGround() {
	// Check for falling
	inAir = true;

	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1 && velocityY > 0) {
			dy = Ground::GetX_Height(grounds[i], abs(ViewPointX) + x) - GetHeight() - y + ViewPointY - ViewPointYInit;

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
			direction = Direction::LEFT;
		}
		else if (dx < 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			dx = 0;
			direction = Direction::RIGHT;
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

	if ((action != Action::LEAVE) && (y + dy < 0)) {
		dy = -y;
	}
	else if (y + dy > 600) {
		dy = 600 - y;
	}
}

void Prisoner::changeAnimation() {
	animationRange = animationRanges[static_cast<int>(sprite)];
	animationDelay = animationDelays[static_cast<int>(sprite)];
	SetFrameIndexOfBitmap(animationRange.first + ((flip) ? animationflipBias : 0));
}

void Prisoner::updateAnimation() {
	if (clock() - start > animationDelay) {
		int frameIndex = GetFrameIndexOfBitmap();
		int animationBias = (flip) ? animationflipBias : 0;
		int totalFrames = animationRange.second - animationRange.first;
		int newFrameIndex = (frameIndex - animationRange.first - animationBias + 1) % totalFrames;
		int frameOffset = newFrameIndex + animationRange.first + animationBias;
		SetFrameIndexOfBitmap(frameOffset);

		animationDone = (frameOffset - animationRange.first) % totalFrames == 0;

		start = clock();
	}
}

std::string Prisoner::getAction() const {
	switch (action) {
	case Prisoner::Action::TIED:
		return "TIED";
	case Prisoner::Action::RESCUED:
		return "RESCUED";
	case Prisoner::Action::MOVE:
		return "MOVE";
	case Prisoner::Action::REWARD:
		return "REWARD";
	case Prisoner::Action::LEAVE:
		return "LEAVE";
	default:
		return "NONE";
	}
}
*/
