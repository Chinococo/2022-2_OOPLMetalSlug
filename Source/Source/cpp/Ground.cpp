#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Ground::Ground(std::pair<int,int> _topLeft, std::pair<int, int> _size) {
	topLeft = _topLeft;
	size = _size;
}

int Ground::isOverlap(CMovingBitmap bmp, Ground ground) {
	int bmp1Left = ground.topLeft.first;
	int bmp1Top = ground.topLeft.second;
	int bmp1Right = bmp1Left + ground.size.first;
	int bmp1Bottom = bmp1Top + ground.size.second;

	int bmp2Left = bmp.GetLeft();
	int bmp2Top = bmp.GetTop();
	int bmp2Right = bmp2Left + bmp.GetWidth();
	int bmp2Bottom = bmp2Top + bmp.GetHeight();

	bool overlapX = bmp1Right >= bmp2Left && bmp2Right >= bmp1Left;
	bool overlapY = bmp1Bottom >= bmp2Top && bmp2Bottom >= bmp1Top;
	if (overlapX && overlapY) {
		if (bmp2Bottom <= bmp1Top) {
			return -1;
		}
		else {
			return 1; 
		}
	}
	else {
		return 0; 
	}
}
