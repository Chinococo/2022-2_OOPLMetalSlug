#include "stdafx.h"
#include "../header/GameStorage.h"

Grenade::Grenade(int absolutePositionLeft, int absolutePositionTop, Direction directionHorizontal)
	: Character(absolutePositionLeft, absolutePositionTop, 5),
	absolutePositionLeft(absolutePositionLeft),
	absolutePositionTop(absolutePositionTop),
	directionHorizontal(directionHorizontal)
{
	
}

void Grenade::init(void) {
	std::vector<std::string> paths;
	CsvReader::readCsv(&animationRanges, &animationDelays, &animationflipBias, &paths, "grenade");
	LoadBitmapByString(paths, RGB(0, 0, 0));
}

void Grenade::update(void) {
	if (!alive) {
		return;
	}

	switch (action) {
	case Action::MOVE:
		handleActionMove();
		ASSERT(sprite == Sprite::MOVE);
		break;
	case Action::EXPLODE:
		handleActionExplode();
		ASSERT(sprite == Sprite::EXPLODE);
		break;
	}

	absolutePositionLeft += (directionHorizontal == Direction::LEFT) ? -distanceHorizontal : distanceHorizontal;
	absolutePositionTop += distanceVertical;

	SetTopLeft(absolutePositionLeft + ViewPointX, absolutePositionTop + ViewPointY - ViewPointYInit);

	nextFrame();
}

void Grenade::draw(void) {
	if (alive) {
		ShowBitmap(2.0);
	}
	else {
		UnshowBitmap();
	}
}

void Grenade::handleActionMove(void) {
	if (sprite != Sprite::MOVE) {
		switchSprite(Sprite::MOVE);
		ASSERT(GetFrameIndexOfBitmap() == 0 || GetFrameIndexOfBitmap() == 32);
	}
	distanceHorizontal = max(0, distanceHorizontal - 1);
	distanceVertical = min(20, distanceVertical + 3);
	if (directionHorizontal != lastDirectionHorizontal) {
		switchSprite(Sprite::MOVE);
	}
	handleGroundCollision();
	if (dying) {
		action = Action::EXPLODE;
	}
}

void Grenade::handleActionExplode(void) {
	if (sprite != Sprite::EXPLODE) {
		switchSprite(Sprite::EXPLODE);
		ASSERT(GetFrameIndexOfBitmap() == 12 || GetFrameIndexOfBitmap() == 44);
	}
	handleGroundCollision();
	if (animationDone) {
		alive = false;
	}
}

bool Grenade::isExpired(void) const {
	auto nowTime = std::chrono::steady_clock::now();
	return nowTime - spawnTime > std::chrono::milliseconds(2000);
}

ColBox Grenade::explode(void) {
	dying = true;
	return {
		{absolutePositionLeft, absolutePositionTop},
		{absolutePositionLeft + GetWidth(), absolutePositionTop + GetHeight()}
	};
}

void Grenade::handleGroundCollision(void) {
	for (const auto &ground : grounds) {
		if (Ground::isOnGround(*this, ground) == 1) {
			const int relPosLeft = abs(ViewPointX) + absolutePositionLeft;
			const int relPosBottom = GetHeight() - absolutePositionTop;
			distanceVertical = Ground::GetX_Height(ground, relPosLeft) - relPosBottom;
		}
	}
}

void Grenade::switchSprite(Sprite sprite) {
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::LEFT) ? animationflipBias : 0;

	int frameOffset = range.first + bias;

	lastDirectionHorizontal = directionHorizontal;
	this->sprite = sprite;

	SetFrameIndexOfBitmap(frameOffset);
}

void Grenade::nextFrame(void) {
	std::pair<int, int> range = animationRanges[static_cast<int>(sprite)];
	int bias = (directionHorizontal == Direction::LEFT) ? animationflipBias : 0;

	int frameIndex = GetFrameIndexOfBitmap();
	int totalFrames = range.second - range.first;
	int newFrameIndex = (frameIndex - range.first - bias + 1 + totalFrames) % totalFrames;
	int frameOffset = newFrameIndex + range.first + bias;

	animationDone = (frameOffset - range.first + totalFrames) % totalFrames == totalFrames - 1;

	SetFrameIndexOfBitmap(frameOffset);
}

ColBox Grenade::getColBox(void) {
	return {
		{absolutePositionLeft, absolutePositionTop},
		{absolutePositionLeft + GetWidth(), absolutePositionTop + GetHeight()}
	};
}
