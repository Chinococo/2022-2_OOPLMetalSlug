#include "stdafx.h"
#include "../header/GameStorage.h"

Grenade::Grenade(int absolutePositionLeft, int absolutePositionTop, Direction directionHorizontal)
	: Character(absolutePositionLeft, absolutePositionTop, 5),
	absolutePositionLeft(absolutePositionLeft),
	absolutePositionTop(absolutePositionTop),
	directionHorizontal(directionHorizontal) {}

void Grenade::init(void) {
	std::vector<std::string> paths;
	CsvReader::readCsv(&animationRanges, &animationDelays, &animationflipBias, &paths, "grenade");
	LoadBitmapByString(paths, RGB(0, 0, 0));
}

void Grenade::update(void) {
	if (!alive) {
		return;
	}
	distanceHorizontal = max(0, distanceHorizontal -1);
	distanceVertical = min(20, distanceVertical + 3);
	for (size_t i = 0; i < grounds.size(); i++) {
		if (Ground::isOnGround(*this, grounds[i]) == 1) {
			distanceVertical = Ground::GetX_Height(grounds[i], abs(ViewPointX) + absolutePositionLeft) - GetHeight() - absolutePositionTop;
		}
	}
	absolutePositionLeft += (directionHorizontal == Direction::LEFT) ? -distanceHorizontal : distanceHorizontal;
	absolutePositionTop += distanceVertical;

	SetTopLeft(absolutePositionLeft + ViewPointX, absolutePositionTop + ViewPointY - ViewPointYInit);
}

void Grenade::draw(void) {
#if 0
	ShowBitmap(2.0);
#else
	if (alive) {
		ShowBitmap(2.0);
	}
	else {
		UnshowBitmap();
	}
#endif
}

void Grenade::explode(void) {
	// create explosion effect
}

void Grenade::handleGroundCollision(void) {
	for (const auto &ground : grounds) {
		if (Ground::isOnGround(*this, ground) == 1) {
			explode();
			alive = false;
		}
	}
}

void Grenade::nextFrame(void) {
	auto range = animationRanges[0];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;

	int frameIndex = GetFrameIndexOfBitmap();
	int totalFrames = range.second - range.first;
	int newFrameIndex = (frameIndex - range.first - bias + 1 + totalFrames) % totalFrames;
	int frameOffset = newFrameIndex + range.first + bias;

	SetFrameIndexOfBitmap(frameOffset);
}
