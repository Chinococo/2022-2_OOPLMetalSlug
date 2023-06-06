#pragma once
#include "Character.h"

class Vec2 {
private:
	std::pair<int, int> vec2 = { 0, 0 };

public:
	Vec2(std::pair<int, int> vec2);
	Vec2(std::initializer_list<int> values);
	int getHoriz(void) const;
	int getVert(void) const;
	Vec2 &setHoriz(int horiz);
	Vec2 &setVert(int vert);
	Vec2 operator+(const Vec2 &other) const;
	Vec2 &operator+=(const Vec2 &other);
};

class RectBox {
private:
	int left = 0;
	int top = 0;
	int right = 0;
	int bottom = 0;
	int width = 0;
	int height = 0;

public:
	RectBox(int left, int top, int width, int height);
	RectBox(std::initializer_list<int> values);
	int getLeft(void) const;
	int getTop(void) const;
	int getRight(void) const;
	int getBottom(void) const;
	int getWidth(void) const;
	int getHeight(void) const;
	ColBox getColBox(void) const;
	RectBox getRelRectBox(void) const;
	RectBox &setLeft(int left);
	RectBox &setTop(int top);
	RectBox &setWidth(int width);
	RectBox &setHeight(int height);
	RectBox &setTopLeft(Vec2 vec2);
	RectBox &setBottomRight(Vec2 vec2);
	RectBox &addTopLeft(Vec2 vec2);
	RectBox &addBottomRight(Vec2 vec2);
};

class Pickup : public Character {
private:
	RectBox absRectBox = { 0, 0, 0, 0 };
	Vec2 accel = { 0, 0 };
	Vec2 vel = { 0, 0 };
	Vec2 dist = { 0, 0 };

public:
	Pickup(int absLeft, int absTop);
	RectBox getAbsRectBox(void) const;
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	void handleGroundCollision(void);
	static void createPickup(int absLeft, int absTop);
};
