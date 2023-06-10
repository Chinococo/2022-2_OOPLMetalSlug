#include "stdafx.h"
#include "../header/GameStorage.h"

TankCannonShell::TankCannonShell(int absPosLeft, int absPosTop, Direction dirHoriz) :
	Character(absPosLeft, absPosTop, 10),
	accel{ 0, GRAVITY },
	vel{ (dirHoriz == Direction::RIGHT) ? 10 : -10, -10 },
	dist{ 0, 0 },
	absRectBox{ absPosLeft, absPosTop, 20, 20 },
	dirHoriz(dirHoriz),
	spawnTime(std::chrono::steady_clock::now())
{

}

void TankCannonShell::init(void) {
	std::vector<std::string> paths;
	CsvReader::readCsv(&animationRanges, &animationDelays, &animationflipBias, &paths, "tank_cannon_shell");
	LoadBitmapByString(paths, RGB(0, 177, 64));
}

void TankCannonShell::update(void) {
	if (!isAlive) {
		return;
	}
	dist = { 0, 0 };
	vel += accel;
	dist += vel;
	handleGroundCollision();
	absRectBox.addTopLeft(dist);
	SetTopLeft(
		absRectBox.getRelRectBox().getLeft(),
		absRectBox.getRelRectBox().getTop()
	);
}

void TankCannonShell::draw(void) {
	if (isAlive) {
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

void TankCannonShell::handleGroundCollision(void) {
	for (const auto &ground : grounds) {
		if (Ground::isOnGround(*this, ground) == 1) {
			explode();
		}
	}
}

bool TankCannonShell::isExpired(void) {
	auto nowTime = std::chrono::steady_clock::now();
	return nowTime - spawnTime > std::chrono::seconds(3);
}

ColBox TankCannonShell::explode(void) {
	isAlive = false;
	return absRectBox.getColBox();
}

RectBox TankCannonShell::getAbsRectBox(void) const {
	return absRectBox;
}

TankCannonShell TankCannonShell::create(int absLeft, int absTop, Direction dirHoriz) {
	TankCannonShell tankCannonShell(absLeft, absTop, dirHoriz);
	tankCannonShell.init();
	return tankCannonShell;
}
