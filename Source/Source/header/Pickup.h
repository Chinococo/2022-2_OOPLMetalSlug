#pragma once
#include "RectBox.h"

class Pickup : public Character {
private:
	RectBox absRectBox = { 0, 0, 0, 0 };
	Vec2 accel = { 0, 0 };
	Vec2 vel = { 0, 0 };
	Vec2 dist = { 0, 0 };
	Pickup(int absLeft, int absTop);

public:
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	void handleGroundCollision(void);
	RectBox getAbsRectBox(void) const;
	static void createPickup(int absLeft, int absTop);
};
