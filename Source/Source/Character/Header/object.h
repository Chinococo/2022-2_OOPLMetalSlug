#pragma once
#include "../../../Library/gameutil.h"

class Object {
protected:
	Object();
	game_framework::CMovingBitmap texture;
	bool showTexture;
	int fallingSpeed;
	enum class Facing {
		LEFT, RIGHT
	} facing;
public:
	int getLeftX();
	int getTopY();
	int getHeight();
	int getWidth();
	void setTopLeft(int _leftX, int _topY);
	void show();
	void unshow();
	bool isCollide(Object object);
};
