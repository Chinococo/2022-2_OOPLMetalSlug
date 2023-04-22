#pragma once
#include "../Library/gameutil.h"

class Ground {
public:
	Ground(std::pair<int, int> _start, std::pair<int, int> _end);
	static int isOnGround(game_framework::CMovingBitmap bmp, Ground ground);
	static int isOnGroundLeft(game_framework::CMovingBitmap bmp, Ground ground);
	static int isOnGroundRight(game_framework::CMovingBitmap bmp, Ground ground);
	static bool LineSegmentIntersection(pair<pair<int, int>, pair<int, int>> line1, pair<pair<int, int>, pair<int, int>> line2);
	static bool onSegment(pair<int, int> p, pair<int, int> q, pair<int, int> r);
	static int orientation(pair<int, int> p, pair<int, int> q, pair<int, int> r);
	std::pair<int, int> start;
	std::pair<int, int> end;
};
