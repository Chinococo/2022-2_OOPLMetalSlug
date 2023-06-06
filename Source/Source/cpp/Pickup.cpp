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

int Vec2::getHoriz(void) const {
	return this->vec2.first;
}
int Vec2::getVert(void) const {
	return this->vec2.second;
}

Vec2 &Vec2::setHoriz(int horiz) {
	this->vec2.first = horiz;
	return *this;
}

Vec2 &Vec2::setVert(int vert) {
	this->vec2.second = vert;
	return *this;
}

Vec2 Vec2::operator+(const Vec2 &other) const {
	return Vec2(this->vec2) += other.vec2;
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

int RectBox::getLeft(void) const {
	return this->left;
}

int RectBox::getTop(void) const {
	return this->top;
}

int RectBox::getRight(void) const {
	return this->right;
}

int RectBox::getBottom(void) const {
	return this->bottom;
}

int RectBox::getWidth(void) const {
	return this->width;
}

int RectBox::getHeight(void) const {
	return this->height;
}

ColBox RectBox::getColBox(void) const {
	return {
		{this->left, this->top},
		{this->right, this->bottom}
	};
}

RectBox RectBox::getRelRectBox(void) const {
	return RectBox(
		this->left + ViewPointX,
		this->top - ViewPointY + ViewPointYInit,
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

RectBox &RectBox::setTopLeft(Vec2 vec2) {
	this->left = vec2.getHoriz();
	this->top = vec2.getVert();
	this->right = vec2.getHoriz() + this->width;
	this->bottom = vec2.getVert() + this->height;
	return *this;
}

RectBox &RectBox::setBottomRight(Vec2 vec2) {
	this->left = vec2.getHoriz() - this->width;
	this->top = vec2.getVert() - this->height;
	this->right = vec2.getHoriz();
	this->bottom = vec2.getVert();
	return *this;
}

RectBox &RectBox::addTopLeft(Vec2 vec2) {
	this->left += vec2.getHoriz();
	this->top += vec2.getVert();
	this->right = this->left + this->width;
	this->bottom = this->top + this->height;
	return *this;
}

RectBox &RectBox::addBottomRight(Vec2 vec2) {
	this->right += vec2.getHoriz();
	this->bottom += vec2.getVert();
	this->left = this->right - this->width;
	this->top = this->bottom - this->height;
	return *this;
}

Pickup::Pickup(int absLeft, int absTop)
	: Character(absLeft, absTop, 0), absRectBox(absLeft, absTop, 50, 50) {
	accel = { 0, GRAVITY };
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
			const int relPosBottom = absRectBox.getRelRectBox().getBottom();
			dist.setVert(Ground::GetX_Height(ground, relPosLeft) - relPosBottom);
			vel = { 0, 0 };
		}
	}
}

void Pickup::createPickup(int absLeft, int absTop) {
	Pickup pickup = Pickup(absLeft, absTop);
	pickup.init();
	pickups.push_back(pickup);
}
