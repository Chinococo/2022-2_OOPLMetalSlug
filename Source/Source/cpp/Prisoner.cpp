#include "stdafx.h"
#include "../header/GameStorage.h"

Prisoner::Prisoner(int absolutePositionLeft, int absolutePositionTop)
	: Character(absolutePositionLeft, absolutePositionTop, velocityHorizontal),
	absolutePositionLeft(absolutePositionLeft),
	absolutePositionTop(absolutePositionTop),
	absoluteAnchorHorizontal(absolutePositionLeft) {}

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

	switchSprite(Sprite::TIED);
}

void Prisoner::update() {
	if (!alive) {
		return;
	}

	//-----------------------------

	distanceHorizontal = 0;
	distanceVertical = 0;

	switch (action) {
	case Action::TIED:
		handleActionTied();
		break;
	case Action::RESCUED:
		handleActionRescued();
		break;
	case Action::MOVE:
		handleActionMove();
		break;
	case Action::FALL:
		handleActionFall();
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

	//-----------------------------

	int relativePositionLeft = absolutePositionLeft + ViewPointX;
	int relativePositionTop = absolutePositionTop - ViewPointY + ViewPointYInit;

	SetTopLeft(relativePositionLeft, relativePositionTop);

	//-----------------------------

	auto delayMillisecond = std::chrono::milliseconds(animationDelays[static_cast<int>(sprite)]);
	auto timePointNow = std::chrono::steady_clock::now();
	auto elapsedMilliSecond = std::chrono::duration_cast<std::chrono::milliseconds>(timePointNow - spriteTimer);

	if (elapsedMilliSecond >= delayMillisecond) {
		nextFrame();
		spriteTimer = timePointNow;
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

void Prisoner::handleActionTied() {
	if (sprite != Sprite::TIED) {
		switchSprite(Sprite::TIED);
	}

	//-----------------------------

	moveVertically(Direction::DOWN);

	//-----------------------------

	handleGroundCollision();
	handleWallCollision();

	//-----------------------------

	bool isRescuredByHeroKnife = isCollideWith(marco) && marco.isAttacking();
	bool isRescuredByHeroBullet = false;

	for (size_t i = 0; i < bullets.size(); i++) {
		if (bullets[i].owner == "hero" && isCollideWith(bullets[i])) {
			isRescuredByHeroBullet = true;
			break;
		}
	}

	if (isRescuredByHeroKnife || isRescuredByHeroBullet) {
		action = Action::RESCUED;
	}
}

void Prisoner::handleActionRescued() {
	if (sprite != Sprite::RESCUED) {
		switchSprite(Sprite::RESCUED);
	}

	//-----------------------------

	moveVertically(Direction::DOWN);

	//-----------------------------

	handleGroundCollision();
	handleWallCollision();

	//-----------------------------

	if (animationDone) {
		action = Action::MOVE;
	}
}

void Prisoner::handleActionMove() {
	if (sprite != Sprite::MOVE) {
		switchSprite(Sprite::MOVE);
	}
	
	//-----------------------------

	int newPositionHorizontal = absolutePositionLeft + distanceHorizontal;
	int distanceFromAnchorHorizontal = abs(newPositionHorizontal - absoluteAnchorHorizontal);

	if (distanceFromAnchorHorizontal > WANDER_DISTANCE) {
		if (directionHorizontal == Direction::LEFT) {
			directionHorizontal = Direction::RIGHT;
		}
		else if (directionHorizontal == Direction::RIGHT) {
			directionHorizontal = Direction::LEFT;
		}
	}

	moveHorizontally(directionHorizontal);
	moveVertically(Direction::DOWN);
	
	//-----------------------------

	handleWallCollision();
	handleGroundCollision();

	//-----------------------------

	if (isCollideWith(marco)) {
		action = Action::REWARD;
	}
	else if (inAir) {
		action = Action::FALL;
	}
}

void Prisoner::handleActionFall() {
	if (sprite != Sprite::FALL) {
		switchSprite(Sprite::FALL);
	}
	
	//-----------------------------

	moveVertically(Direction::DOWN);

	//-----------------------------

	handleWallCollision();
	handleGroundCollision();

	//-----------------------------

	if (!inAir) {
		action = Action::MOVE;
	}
}

void Prisoner::handleActionReward() {
	if (sprite != Sprite::REWARD) {
		switchSprite(Sprite::REWARD);
	}

	//-----------------------------

	// Build a new pickup here (point pickup or weapon pickup)

	//-----------------------------

	moveVertically(Direction::DOWN);

	//-----------------------------

	handleWallCollision();
	handleGroundCollision();

	//-----------------------------

	if (animationDone) {
		switchSprite(Sprite::MOVE);
		action = Action::LEAVE;
	}
}

void Prisoner::handleActionLeave() {
	if (sprite != Sprite::MOVE) {
		switchSprite(Sprite::MOVE);
	}

	//-----------------------------

	moveHorizontally(Direction::LEFT);
	moveVertically(Direction::DOWN);

	//-----------------------------

	handleGroundCollision();

	//-----------------------------

	int relativePositionRight = absolutePositionLeft + ViewPointX + GetWidth();

	if (relativePositionRight < 0) {
		alive = false;
	}
}

void Prisoner::moveHorizontally(Direction direction) {
	if (direction == Direction::LEFT) {
		distanceHorizontal -= velocityHorizontal;
	}
	else if (direction == Direction::RIGHT) {
		distanceHorizontal += velocityHorizontal;
	}

	//-----------------------------

	directionHorizontal = direction;
}

void Prisoner::moveVertically(Direction direction) {
	if (direction == Direction::UP) {
		velocityVertical = -15;
	}
	else if (direction == Direction::DOWN) {
		velocityVertical += GRAVITY;
	}
	else if (direction == Direction::NONE) {
		velocityVertical = 0;
	}
	distanceVertical += velocityVertical;

	//-----------------------------

	directionVertical = direction;
}

bool Prisoner::isCollideWith(Character other) {
	int relativePositionLeft = absolutePositionLeft + ViewPointX;
	int relativePositionTop = absolutePositionTop - ViewPointY + ViewPointYInit;

	int relativeCollisionBoxLeft = relativePositionLeft + collisionBoxTweakLeft;
	int relativeCollisionBoxTop = relativePositionTop + collisionBoxTweakTop;

	int relativeCollisionBoxRight = relativeCollisionBoxLeft + collisionBoxWidth;
	int relativeCollisionBoxBottom = relativeCollisionBoxTop + collisionBoxHeight;

	int otherRelativePositionLeft = other.GetLeft();
	int otherRelativePositionTop = other.GetTop();
	int otherRelativePositionRight = otherRelativePositionLeft + other.GetWidth();
	int otherRelativePositionBottom = otherRelativePositionTop + other.GetHeight();

	if (relativeCollisionBoxRight < otherRelativePositionLeft ||
		otherRelativePositionRight < relativeCollisionBoxLeft ||
		relativeCollisionBoxBottom < otherRelativePositionTop ||
		otherRelativePositionBottom < relativeCollisionBoxTop
	) {
		return false;
	}

	return true;
}

void Prisoner::handleWallCollision() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (distanceHorizontal > 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			distanceHorizontal = 0;
			directionHorizontal = Direction::LEFT;
			break;
		}
		else if (distanceHorizontal < 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			distanceHorizontal = 0;
			directionHorizontal = Direction::RIGHT;
			break;
		}
	}
}

void Prisoner::handleGroundCollision() {
	inAir = true;

	for (size_t i = 0; i < grounds.size(); i++) {
		if (velocityVertical > 0 && Ground::isOnGround(*this, grounds[i]) == 1) {
			int relativePositionTop = absolutePositionTop - ViewPointY + ViewPointYInit;
			int relativeCollisionBoxTop = relativePositionTop + collisionBoxTweakTop;
			int relativeCollisionBoxBottom = relativeCollisionBoxTop + collisionBoxHeight;

			distanceVertical = Ground::GetX_Height(grounds[i], absolutePositionLeft) - relativeCollisionBoxBottom;

			inAir = false;
			velocityVertical = 0;
			break;
		}
	}
}

void Prisoner::switchSprite(Sprite sprite) {
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;
	
	int frameOffset = range.first + bias;

	this->sprite = sprite;
	
	SetFrameIndexOfBitmap(frameOffset);
}

void Prisoner::nextFrame() {
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;

	int frameIndex = GetFrameIndexOfBitmap();
	int totalFrames = range.second - range.first;
	int newFrameIndex = (frameIndex - range.first - bias + 1 + totalFrames) % totalFrames;
	int frameOffset = newFrameIndex + range.first + bias;

	animationDone = (frameOffset - range.first + totalFrames) % totalFrames == totalFrames - 1;

	SetFrameIndexOfBitmap(frameOffset);
}

int Prisoner::getAbsLeft() const {
	return absolutePositionLeft;
}

int Prisoner::getAbsTop() const {
	return absolutePositionTop;
}

int Prisoner::getAbsFrame() {
	return GetFrameIndexOfBitmap();
}

int Prisoner::getRelFrame() {
	int frameIndex = GetFrameIndexOfBitmap();
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	return frameIndex - range.first - bias;
}

std::string Prisoner::getDirectionHorizontal() const {
	switch (directionHorizontal) {
	case Direction::NONE:
		return "NONE";
	case Direction::UP:
		return "UP";
	case Direction::DOWN:
		return "DOWN";
	case Direction::LEFT:
		return "LEFT";
	case Direction::RIGHT:
		return "RIGHT";
	default:
		return "NULL";
	}
}

std::string Prisoner::getSprite() const {
	switch (sprite) {
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
		return "NULL";
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
	case Prisoner::Action::FALL:
		return "FALL";
	case Prisoner::Action::REWARD:
		return "REWARD";
	case Prisoner::Action::LEAVE:
		return "LEAVE";
	default:
		return "NULL";
	}
}

bool Prisoner::isAnimationDone() const {
	return animationDone;
}
