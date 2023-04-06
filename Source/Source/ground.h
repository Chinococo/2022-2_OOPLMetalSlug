#pragma once
#include "../Library/gameutil.h"

class Ground : public game_framework::CMovingBitmap {
public:
	Ground();
	virtual ~Ground();
	static bool isOverlap(CMovingBitmap bmp, Ground ground);
		
};
