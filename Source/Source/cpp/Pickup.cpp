#include "stdafx.h"
#include "../header/GameStorage.h"

Pickup::Pickup(int absLeft, int absTop)
	: Character(absLeft, absTop, 0), absRectBox(absLeft, absTop, 20, 20), accel{ 0, GRAVITY } {

}

RectBox Pickup::getAbsRectBox(void) const {
	return absRectBox;
}

void Pickup::init(void) {
	std::vector<std::string> paths;
	CsvReader::readCsv(&animationRanges, &animationDelays, &animationflipBias, &paths, "pickup");
	LoadBitmapByString(paths, RGB(0, 177, 64));
}

void Pickup::update(void) {
	if (!alive) {
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

void Pickup::draw(void) {
	if (alive) {
		ShowBitmap(1.5);
	}
	else {
		UnshowBitmap();
	}
}

void Pickup::handleGroundCollision(void) {
	for (const auto &ground : grounds) {
		if (Ground::isOnGround(*this, ground) == 1) {
			const int relPosLeft = absRectBox.getRelRectBox().getLeft();
			const int relPosTop = absRectBox.getRelRectBox().getTop();
			dist.setVert(Ground::GetX_Height(ground, relPosLeft) - relPosTop - GetHeight());
			vel = { 0, 0 };
		}
	}
}

void Pickup::createPickup(int absLeft, int absTop) {
	Pickup pickup = Pickup(absLeft, absTop);
	pickup.init();
	pickups.push_back(pickup);
}
