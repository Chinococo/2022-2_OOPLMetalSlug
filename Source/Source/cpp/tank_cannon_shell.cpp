#include "stdafx.h"
#include "../header/GameStorage.h"

TankCannonShell::TankCannonShell(int absPosLeft, int absPosTop, Direction dirHoriz) :
	Character(absPosLeft, absPosTop, 10),
	accel{ (dirHoriz == Direction::RIGHT) ? 1 : -1, GRAVITY },
	absPos{ absPosLeft, absPosTop },
	dirHoriz(dirHoriz) {

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
			isAlive = false;
		}
	}
}

void TankCannonShell::dead(void) {
	isAlive = false;
}

RectBox TankCannonShell::getAbsRectBox(void) const {
	return absRectBox;
}

TankCannonShell TankCannonShell::create(int absLeft, int absTop, Direction dirHoriz) {
	TankCannonShell tankCannonShell(absLeft, absTop, dirHoriz);
	tankCannonShell.init();
	return tankCannonShell;
}
