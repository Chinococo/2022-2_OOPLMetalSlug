#pragma once
#include "../Library/gameutil.h"

class Ground {
public:
	Ground(std::pair<int, int> _topLeft, std::pair<int, int> _size);
	static int isOverlap(game_framework::CMovingBitmap bmp, Ground ground);

	std::pair<int, int> topLeft;
	std::pair<int, int> size;
};
