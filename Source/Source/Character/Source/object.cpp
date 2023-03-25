#include "../Header/object.h"
#include "../../../Library/gameutil.h"

Object::Object() {
	facing = Facing::RIGHT;
}

int Object::getLeftX() {
	return texture.GetLeft();
}

int Object::getTopY() {
	return texture.GetTop();
}

int Object::getHeight() {
	return texture.GetHeight();
}

int Object::getWidth() {
	return texture.GetWidth();
}

void Object::setTopLeft(int _leftX, int _topY) {
	texture.SetTopLeft(_leftX, _topY);
}

void Object::show() {
	showTexture = true;
}

void Object::unshow() {
	showTexture = false;
}

bool Object::isCollide(Object object) {
	return game_framework::CMovingBitmap::IsOverlap(this->texture, object.texture);
}
