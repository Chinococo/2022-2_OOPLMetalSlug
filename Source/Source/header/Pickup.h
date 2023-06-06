#pragma once
#include "Character.h"

class Vec2 {
private:
	std::pair<int, int> vec2;

public:
	Vec2(std::pair<int, int> vec2);
	Vec2(std::initializer_list<int> values);
	Vec2 &setHoriz(int horiz);
	Vec2 &setVert(int vert);
	Vec2 operator+(const Vec2 &other);
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
	int getLeft(void);
	int getTop(void);
	int getRight(void);
	int getBottom(void);
	int getWidth(void);
	int getHeight(void);
	ColBox getColBox(void);
	RectBox getRelRectBox(void);
	RectBox &setLeft(int left);
	RectBox &setTop(int top);
	RectBox &setWidth(int width);
	RectBox &setHeight(int height);
};

class Pickup : public Character {
private:
	RectBox absRectBox = { 0, 0, 0, 0 };
	Vec2 accel = { 0, 0 };
	Vec2 vel = { 0, 0 };
	Vec2 dist = { 0, 0 };

public:
	Pickup(int left, int top);
	RectBox getAbsRectBox(void);
	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	void handleGroundCollision(void);
};
