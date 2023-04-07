#pragma once
#include "../Library/gameutil.h"

class Ground : public game_framework::CMovingBitmap {
public:
	Ground(int x1,int y1,int x2,int y2 );
	Ground(int X1, int Y1, int X2, int Y2, int Top, int Left,int width,int height);
	virtual ~Ground();
	static int isOverlap(CMovingBitmap bmp, Ground ground);
private:
	int x1,y1,x2,y2;
};
