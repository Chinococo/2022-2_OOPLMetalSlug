#pragma once
#include "RectBox.h"

class TankCannonShell : public Character {
private:
	RectBox absRectBox = { 0, 0, 0, 0 };
	Vec2 accel = { 0, 0 };
	Vec2 vel = { 0, 0 };
	Vec2 dist = { 0, 0 };
	Vec2 absPos = { 0, 0 };
	Direction dirHoriz = Direction::NONE;
	TankCannonShell(int absPosLeft, int absPosTop, Direction dirHoriz);

public:
	bool isAlive = true;
	void init(void);
	void update(void);
	void draw(void);
	void handleGroundCollision(void);
	virtual void dead(void) override;
	RectBox getAbsRectBox(void) const;
	static TankCannonShell create(int absLeft, int absTop, Direction dirHoriz);
};
