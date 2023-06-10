#pragma once
#include "RectBox.h"

class TankCannonShell : public Character {
private:
	Vec2 accel;
	Vec2 vel;
	Vec2 dist;
	RectBox absRectBox;
	Direction dirHoriz;
	std::chrono::time_point<std::chrono::steady_clock> spawnTime;
	TankCannonShell(int absPosLeft, int absPosTop, Direction dirHoriz);

public:
	bool isAlive = true;
	void init(void);
	void update(void);
	void draw(void);
	void handleGroundCollision(void);
	bool isExpired(void);
	ColBox explode(void);
	RectBox getAbsRectBox(void) const;
	static TankCannonShell create(int absLeft, int absTop, Direction dirHoriz);
};
