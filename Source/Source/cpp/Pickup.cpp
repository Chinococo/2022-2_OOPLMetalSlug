#include "stdafx.h"
#include "../header/GameStorage.h"

Vec2::Vec2(std::pair<int, int> vec2)
	: vec2(vec2) {
	
}

Vec2::Vec2(std::initializer_list<int> values) {
	if (values.size() != 2) {
		throw std::invalid_argument("The number of arguments must be 2.");
	}
	auto it = values.begin();
	this->vec2.first = *(it++);
	this->vec2.second = *it;
}

Vec2 &Vec2::setHoriz(int horiz) {
	this->vec2.first = horiz;
	return *this;
}

Vec2 &Vec2::setVert(int vert) {
	this->vec2.second = vert;
	return *this;
}

Vec2 Vec2::operator+(const Vec2 &other) {
	return Vec2(vec2) += other.vec2;
}

Vec2 &Vec2::operator+=(const Vec2 &other) {
	this->vec2.first += other.vec2.first;
	this->vec2.second += other.vec2.second;
	return *this;
}

RectBox::RectBox(int left, int top, int width, int height)
	: left(left), top(top),
	right(left + width), bottom(top + height),
	width(width), height(height) {
}

RectBox::RectBox(std::initializer_list<int> values) {
	if (values.size() != 4) {
		throw std::invalid_argument("The number of arguments must be 4.");
	}
	auto it = values.begin();
	this->left = *(it++);
	this->top = *(it++);
	this->width = *(it++);
	this->height = *it;
}

int RectBox::getLeft(void) {
	return this->left;
}

int RectBox::getTop(void) {
	return this->top;
}

int RectBox::getRight(void) {
	return this->right;
}

int RectBox::getBottom(void) {
	return this->bottom;
}

int RectBox::getWidth(void) {
	return this->width;
}

int RectBox::getHeight(void) {
	return this->height;
}

ColBox RectBox::getColBox(void) {
	return {
		{this->left, this->top},
		{this->right, this->bottom}
	};
}

RectBox RectBox::getRelRectBox(void) {
	return RectBox(
		this->left + abs(ViewPointX),
		this->top + ViewPointY - ViewPointYInit,
		this->width,
		this->height
	);
}

RectBox &RectBox::setLeft(int left) {
	this->left = left;
	this->right = left + this->width;
	return *this;
}

RectBox &RectBox::setTop(int top) {
	this->top = top;
	this->bottom = top + this->height;
	return *this;
}

RectBox &RectBox::setWidth(int width) {
	this->width = width;
	this->right = this->left + width;
	return *this;
}

RectBox &RectBox::setHeight(int height) {
	this->height = height;
	this->bottom = top + height;
	return *this;
}

Pickup::Pickup(int absLeft, int absTop)
	: Character(absLeft, absTop, 0), absRectBox(absLeft, absTop, 50, 50) {
	accel = { 0, GRAVITY };
}

RectBox Pickup::getAbsRectBox(void) {
	return absRectBox;
}

void Pickup::init(void) {
	std::vector<std::string> paths;
	CsvReader::readCsv(&animationRanges, &animationDelays, &animationflipBias, &paths, "pickup");
	LoadBitmapByString(paths, RGB(0, 0, 0));
}

void Pickup::update(void) {
	if (!alive) {
		return;
	}
	vel += accel;
	dist += vel;
	SetTopLeft(
		absRectBox.getRelRectBox().getLeft(),
		absRectBox.getRelRectBox().getTop()
	);
}

void Pickup::draw(void) {
	if (alive) {
		ShowBitmap();
	}
	else {
		UnshowBitmap();
	}
}

void Pickup::handleGroundCollision(void) {
	for (const auto &ground : grounds) {
		if (Ground::isOnGround(*this, ground) == 1) {
			const int relPosLeft = absRectBox.getRelRectBox().getLeft();
			const int relPosBottom = absRectBox.getRelRectBox().getBottom();
			dist.setVert(Ground::GetX_Height(ground, relPosLeft) - relPosBottom);
		}
	}
}
