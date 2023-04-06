#pragma once
#include "../Library/gameutil.h"

class Ground : public game_framework::CMovingBitmap {
public:
	Ground(int x1,int y1,int x2,int y2 );
	virtual ~Ground();
	static bool isOverlap(CMovingBitmap bmp, Ground ground);
private:
	int x1,y1,x2,y2;
};
