#include "stdafx.h"
#include "../header/GameStorage.h"

RShobuBomb::RShobuBomb(int absolutePositionLeft, int absolutePositionTop)
	: Character(absolutePositionLeft, absolutePositionTop, velocityHorizontal),
	absolutePositionLeft(absolutePositionLeft),
	absolutePositionTop(absolutePositionTop) {}

void RShobuBomb::init() {
	std::vector<std::vector<std::string>> csv = readCSV("resources/csv/character.csv");
	std::vector<std::string> paths;
	std::pair<int, int> range;

	for (size_t i = 1; i < csv.size(); i++) {
		if (csv[i][0] != "rshobuBomb")
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
		if (csv[i][0] != "rshobuBomb")
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

void RShobuBomb::update() {
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

void RShobuBomb::draw() {
	if (alive) {
		ShowBitmap(2.2);
	}
	else {
		UnshowBitmap();
	}
}

void RShobuBomb::handleActionMove() {
	if (sprite != Sprite::MOVE) {
		switchSprite(Sprite::MOVE);
	}

	//-----------------------------

	moveVertically(Direction::DOWN);

	//-----------------------------

	handleGroundCollision();

	//-----------------------------

	if (!inAir) {
		alive = false;
	}
}

void RShobuBomb::moveVertically(Direction direction) {
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

bool RShobuBomb::isCollideWith(Character other) {
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

void RShobuBomb::handleWallCollision() {
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

void RShobuBomb::handleGroundCollision() {
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

void RShobuBomb::switchSprite(Sprite sprite) {
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;

	int frameOffset = range.first + bias;

	this->sprite = sprite;

	SetFrameIndexOfBitmap(frameOffset);
}

void RShobuBomb::nextFrame() {
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;

	int frameIndex = GetFrameIndexOfBitmap();
	int totalFrames = range.second - range.first;
	int newFrameIndex = (frameIndex - range.first - bias + 1 + totalFrames) % totalFrames;
	int frameOffset = newFrameIndex + range.first + bias;

	animationDone = (frameOffset - range.first + totalFrames) % totalFrames == totalFrames - 1;

	SetFrameIndexOfBitmap(frameOffset);
}

RShobuBomb &RShobuBomb::operator=(const RShobuBomb &other) {
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

	inAir = other.inAir;
	animationDone = other.animationDone;

	spriteTimer = other.spriteTimer;

	directionHorizontal = other.directionHorizontal;
	directionVertical = other.directionVertical;

	sprite = other.sprite;

	action = other.action;

	return *this;
}
