#include "stdafx.h"
#include "../header/GameStorage.h"

RShobu::RShobu(int absolutePositionLeft, int absolutePositionTop)
	: Character(absolutePositionLeft, absolutePositionTop, velocityHorizontal),
	absolutePositionLeft(absolutePositionLeft),
	absolutePositionTop(absolutePositionTop)
{
	
}

void RShobu::init() {
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;

	for (size_t i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "rshobu")
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
		if (csv[i][0] != "rshobu")
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

	switchSprite(Sprite::MOVE);
}

void RShobu::update() {
	if (!alive) {
		return;
	}

	//-----------------------------

	distanceHorizontal = 0;
	distanceVertical = 0;

	switch (action) {
	case Action::MOVE:
		handleActionMove();
		break;
	case Action::DIE:
		handleActionDie();
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

	//-----------------------------

	bombs.erase(std::remove_if(bombs.begin(), bombs.end(), [](const RShobuBomb &bomb) {
		return !bomb.isAlive();
	}), bombs.end());

	for (size_t i = 0; i < bombs.size(); i++) {
		bombs[i].update();
	}
}

void RShobu::draw() {
	if (alive) {
		for (size_t i = 0; i < bombs.size(); i++) {
			bombs[i].draw();
		}

		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

void RShobu::handleActionMove() {
	if (sprite != Sprite::MOVE) {
		switchSprite(Sprite::MOVE);
	}

	//-----------------------------

	const int fireDelayMilli = (state == "map1") ? FIRE_DELAY_MILLISECOND : FIRE_DELAY_MILLISECOND / 2;

	auto delayMillisecond = std::chrono::milliseconds(FIRE_DELAY_MILLISECOND);
	auto timePointNow = std::chrono::steady_clock::now();
	auto elapsedMilliSecond = std::chrono::duration_cast<std::chrono::milliseconds>(timePointNow - fireTimer);

	if (elapsedMilliSecond >= delayMillisecond) {
		fire();
		fireTimer = timePointNow;
	}

	//-----------------------------

	// Marco position
	int relativeMarcoMiddleHorizontal = marco.GetLeft() + marco.GetWidth() / 2;
	int relativeMarcoMiddleVertical = marco.GetTop() + marco.GetHeight() / 2;

	int absoluteMarcoMiddleHorizontal = relativeMarcoMiddleHorizontal - ViewPointX;
	int absoluteMarcoMiddleVertical = relativeMarcoMiddleVertical - ViewPointY + ViewPointYInit;

	// Tank position
	int relativeTankMiddleHorizontal = marco_tank.GetLeft() + marco_tank.GetWidth() / 2;
	int relativeTankMiddleVertical = marco_tank.GetTop() + marco_tank.GetHeight() / 2;

	int absoluteTankMiddleHorizontal = relativeTankMiddleHorizontal - ViewPointX;
	int absoluteTankMiddleVertical = relativeTankMiddleVertical - ViewPointY + ViewPointYInit;

	// This rshobu position
	int absoluteMiddleHorizontal = absolutePositionLeft + GetWidth() / 2;
	int absoluteMiddleVertical = absolutePositionTop + GetHeight() / 2;

	// Distance
	int distanceToMarcoHorizontal = absoluteMarcoMiddleHorizontal - absoluteMiddleHorizontal;
	int distanceToMarcoVertical = absoluteMarcoMiddleVertical - absoluteMiddleVertical;

	int distanceToTankHorizontal = absoluteTankMiddleHorizontal - absoluteMiddleHorizontal;
	int distanceToTankVertical = absoluteTankMiddleVertical - absoluteMiddleVertical;

	if (Driving) {
		if (distanceToTankHorizontal < -DISTANCE_TO_HERO_HORIZONTAL) {
			moveHorizontally(Direction::LEFT);
		}
		else if (distanceToTankHorizontal > DISTANCE_TO_HERO_HORIZONTAL) {
			moveHorizontally(Direction::RIGHT);
		}

		if (distanceToTankVertical < DISTANCE_TO_HERO_VERTICAL) {
			moveVertically(Direction::UP);
		}
		else if (distanceToTankVertical > DISTANCE_TO_HERO_VERTICAL) {
			moveVertically(Direction::DOWN);
		}
	}
	else {
		if (distanceToMarcoHorizontal < -DISTANCE_TO_HERO_HORIZONTAL) {
			moveHorizontally(Direction::LEFT);
		}
		else if (distanceToMarcoHorizontal > DISTANCE_TO_HERO_HORIZONTAL) {
			moveHorizontally(Direction::RIGHT);
		}

		if (distanceToMarcoVertical < DISTANCE_TO_HERO_VERTICAL) {
			moveVertically(Direction::UP);
		}
		else if (distanceToMarcoVertical > DISTANCE_TO_HERO_VERTICAL) {
			moveVertically(Direction::DOWN);
		}
	}

	//-----------------------------


	handleWallCollision();

	//-----------------------------

	if (health == 0) {
		action = Action::DIE;
	}
}
void RShobu::damge(int damge) {
	health = max(0, health - damge);
}
void RShobu::handleActionDie() {
	if (sprite != Sprite::DIE) {
		switchSprite(Sprite::DIE);
	}

	//-----------------------------

	if (animationDone) {
		alive = false;
	}
}

void RShobu::fire() {
	int absolutePositionMiddleHorizontal = absolutePositionLeft + GetWidth() / 2;
	int absolutePositionMiddleVertical = absolutePositionTop + GetHeight() / 2;

	RShobuBomb bomb(absolutePositionMiddleHorizontal - 10, absolutePositionMiddleVertical);
	bomb.init();
	bombs.push_back(bomb);
}

bool RShobu::isHurt(Character other) {
	for (size_t i = 0; i < bombs.size(); i++) {
		if (bombs[i].isCollideWith(other)) {
			return true;
		}
	}
	return false;
}

std::vector<RShobuBomb> RShobu::getBombs(void) {
	return this->bombs;
}

void RShobu::moveHorizontally(Direction direction) {
	if (direction == Direction::LEFT) {
		distanceHorizontal -= velocityHorizontal;
	}
	else if (direction == Direction::RIGHT) {
		distanceHorizontal += velocityHorizontal;
	}

	//-----------------------------

	directionHorizontal = direction;
}

void RShobu::moveVertically(Direction direction) {
	if (direction == Direction::UP) {
		distanceVertical -= velocityVertical;
	}
	else if (direction == Direction::DOWN) {
		distanceVertical += velocityVertical;
	}
	else if (direction == Direction::NONE) {
		distanceVertical = 0;
	}

	//-----------------------------

	directionVertical = direction;
}

bool RShobu::isCollideWith(Character other) {
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
		otherRelativePositionBottom < relativeCollisionBoxTop)
	{
		return false;
	}

	return true;
}

void RShobu::handleWallCollision() {
	for (size_t i = 0; i < grounds.size(); i++) {
		if (distanceHorizontal > 0 && Ground::isOnGroundLeft(*this, grounds[i]) == 1) {
			distanceHorizontal = 0;
			break;
		}
		else if (distanceHorizontal < 0 && Ground::isOnGroundRight(*this, grounds[i]) == 1) {
			distanceHorizontal = 0;
			break;
		}
	}
}

void RShobu::switchSprite(Sprite sprite) {
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;

	int frameOffset = range.first + bias;

	this->sprite = sprite;

	SetFrameIndexOfBitmap(frameOffset);
}

void RShobu::nextFrame() {
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;

	int frameIndex = GetFrameIndexOfBitmap();
	int totalFrames = range.second - range.first;
	int newFrameIndex = (frameIndex - range.first - bias + 1 + totalFrames) % totalFrames;
	int frameOffset = newFrameIndex + range.first + bias;

	animationDone = (frameOffset - range.first + totalFrames) % totalFrames == totalFrames - 1;

	SetFrameIndexOfBitmap(frameOffset);
}

int RShobu::getAbsLeft() const {
	return absolutePositionLeft;
}

int RShobu::getAbsTop() const {
	return absolutePositionTop;
}

int RShobu::getAbsFrame() {
	return GetFrameIndexOfBitmap();
}

int RShobu::getRelFrame() {
	int frameIndex = GetFrameIndexOfBitmap();
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	return frameIndex - range.first - bias;
}

std::string RShobu::getDirectionHorizontal() const {
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

std::string RShobu::getSprite() const {
	switch (action) {
	case Action::MOVE:
		return "MOVE";
	case Action::DIE:
		return "DIE";
	default:
		return "NULL";
	}
}

std::string RShobu::getAction() const {
	switch (action) {
	case Action::MOVE:
		return "MOVE";
	case Action::DIE:
		return "DIE";
	default:
		return "NULL";
	}
}

bool RShobu::isAnimationDone() const {
	return animationDone;
}

RShobu &RShobu::operator=(const RShobu &other) {
	absolutePositionLeft = other.absolutePositionLeft;
	absolutePositionTop = other.absolutePositionTop;

	distanceHorizontal = other.distanceHorizontal;
	distanceVertical = other.distanceVertical;

	collisionBoxTweakLeft = other.collisionBoxTweakLeft;
	collisionBoxTweakTop = other.collisionBoxTweakTop;

	collisionBoxWidth = other.collisionBoxWidth;
	collisionBoxHeight = other.collisionBoxHeight;

	velocityHorizontal = other.velocityHorizontal;
	velocityVertical = other.velocityVertical;

	animationDone = other.animationDone;

	spriteTimer = other.spriteTimer;

	directionHorizontal = other.directionHorizontal;
	directionVertical = other.directionVertical;

	sprite = other.sprite;

	action = other.action;

	return *this;
}

ColBox RShobu::getColBox(void) {
	return {
		{absolutePositionLeft, absolutePositionTop},
		{absolutePositionLeft + GetWidth(), absolutePositionTop + GetHeight()}
	};
}
