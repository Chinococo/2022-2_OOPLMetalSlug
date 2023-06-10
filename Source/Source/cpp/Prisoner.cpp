#include "stdafx.h"
#include "../header/GameStorage.h"

Prisoner::Prisoner(int absolutePositionLeft, int absolutePositionTop)
	: Character(absolutePositionLeft, absolutePositionTop, velocityHorizontal),
	absolutePositionLeft(absolutePositionLeft),
	absolutePositionTop(absolutePositionTop),
	absoluteAnchorHorizontal(absolutePositionLeft) {}

void Prisoner::init() {
	std::vector<std::string> paths;

	CsvReader::readCsv(&animationRanges, &animationDelays, &animationflipBias, &paths, "prisoner");

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

	if (directionHorizontal != lastDirectionHorizontal) {
		switchSprite(Sprite::TIED);
	}

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

	if (directionHorizontal != lastDirectionHorizontal) {
		switchSprite(Sprite::RESCUED);
	}

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
	
	if (directionHorizontal != lastDirectionHorizontal) {
		switchSprite(Sprite::MOVE);
	}

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

	if (directionHorizontal != lastDirectionHorizontal) {
		switchSprite(Sprite::FALL);
	}

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

	moveVertically(Direction::DOWN);
	
	if (directionHorizontal != lastDirectionHorizontal) {
		switchSprite(Sprite::REWARD);
	}

	//-----------------------------

	handleWallCollision();
	handleGroundCollision();

	//-----------------------------

	if (animationDone) {
		Pickup::createPickup(absolutePositionLeft, absolutePositionTop);
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

	if (directionHorizontal != lastDirectionHorizontal) {
		switchSprite(Sprite::MOVE);
	}

	//-----------------------------

	handleGroundCollision();

	//-----------------------------

	int relativePositionTop = absolutePositionTop - ViewPointY + ViewPointYInit;
	int relativePositionRight = absolutePositionLeft + ViewPointX + GetWidth();

	if (relativePositionRight < 0 || relativePositionTop > 600) {
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

	lastDirectionHorizontal = directionHorizontal;
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
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;

	int frameIndex = GetFrameIndexOfBitmap();
	int totalFrames = range.second - range.first;
	int newFrameIndex = (frameIndex - range.first - bias + 1 + totalFrames) % totalFrames;

	return newFrameIndex;
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
	case Sprite::TIED:
		return "TIED";
	case Sprite::RESCUED:
		return "RESCUED";
	case Sprite::MOVE:
		return "MOVE";
	case Sprite::FALL:
		return "FALL";
	case Sprite::REWARD:
		return "REWARD";
	default:
		return "NULL";
	}
}

std::string Prisoner::getAction() const {
	switch (action) {
	case Action::TIED:
		return "TIED";
	case Action::RESCUED:
		return "RESCUED";
	case Action::MOVE:
		return "MOVE";
	case Action::FALL:
		return "FALL";
	case Action::REWARD:
		return "REWARD";
	case Action::LEAVE:
		return "LEAVE";
	default:
		return "NULL";
	}
}

bool Prisoner::isAnimationDone() const {
	return animationDone;
}

Prisoner &Prisoner::operator=(const Prisoner &other) {
	absolutePositionLeft = other.absolutePositionLeft;
	absolutePositionTop = other.absolutePositionTop;

	absoluteAnchorHorizontal = other.absoluteAnchorHorizontal;

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

void Prisoner::reset(void) {
	absolutePositionLeft = 0;
	absolutePositionTop = 0;

	absoluteAnchorHorizontal = 0;

	distanceHorizontal = 0;
	distanceVertical = 0;

	collisionBoxTweakLeft = 0;
	collisionBoxTweakTop = 0;

	collisionBoxWidth = 50;
	collisionBoxHeight = 90;

	velocityHorizontal = 5;
	velocityVertical = 0;

	inAir = false;
	animationDone = false;

	spriteTimer = std::chrono::steady_clock::now();

	lastDirectionHorizontal = Direction::LEFT;
	directionHorizontal = Direction::LEFT;
	directionVertical = Direction::NONE;

	sprite = Sprite::TIED;

	action = Action::TIED;

	alive = true;

	SetFrameIndexOfBitmap(0);
}
