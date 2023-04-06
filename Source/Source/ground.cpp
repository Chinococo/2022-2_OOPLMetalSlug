#include "stdafx.h"
#include "ground.h"
#include "../Library/gameutil.h"

Ground::Ground(int X1, int Y1, int X2, int Y2) {
	x1 = X1;
	x2 = X2;
	y1 = Y1;
	y1 = Y1; 
	LoadEmptyBitmap(10, 1000);
	SetTopLeft(10, 450);
}
bool Ground::isOverlap(game_framework::CMovingBitmap bmp, Ground ground) {
	
	// 計算 bmp1 的邊界框座標
	int bmp1Left = ground.GetLeft();
	int bmp1Top = ground.GetTop();
	int bmp1Right = bmp1Left + ground.GetWidth();
	int bmp1Bottom = bmp1Top + ground.GetHeight();

	// 計算 bmp2 的邊界框座標
	int bmp2Left = bmp.GetLeft();
	int bmp2Top = bmp.GetTop();
	int bmp2Right = bmp2Left + bmp.GetWidth();
	int bmp2Bottom = bmp2Top + bmp.GetHeight();

	// 檢查 bmp1 和 bmp2 的邊界框是否有重疊
	bool isOverlapX = bmp1Right >= bmp2Left && bmp2Right >= bmp1Left;
	bool isOverlapY = bmp1Bottom >= bmp2Top && bmp2Bottom >= bmp1Top;
	return isOverlapX && isOverlapY;
}
Ground::~Ground() {

}
