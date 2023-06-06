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
	distanceHorizontal = max(0, distanceHorizontal -1);
	distanceVertical = min(20, distanceVertical + 3);
	
	handleGroundCollision();

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

bool Grenade::isExpired(void) const {
	auto nowTime = std::chrono::steady_clock::now();
	return nowTime - spawnTime > std::chrono::seconds(2);
}

ColBox Grenade::explode(void) {
	alive = false;
	return CollideBox;
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

void Grenade::nextFrame(void) {
	auto range = animationRanges[0];
	int bias = (directionHorizontal == Direction::RIGHT) ? animationflipBias : 0;

	int frameIndex = GetFrameIndexOfBitmap();
	int totalFrames = range.second - range.first;
	int newFrameIndex = (frameIndex - range.first - bias + 1 + totalFrames) % totalFrames;
	int frameOffset = newFrameIndex + range.first + bias;

	SetFrameIndexOfBitmap(frameOffset);
}

ColBox Grenade::getColBox(void) {
	return { {absolutePositionLeft, absolutePositionTop}, {absolutePositionLeft + GetWidth(), absolutePositionTop + GetHeight()} };
}
