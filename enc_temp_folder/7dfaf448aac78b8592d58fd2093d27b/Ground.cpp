#include "stdafx.h"
#include "../header/GameStorage.h"

using namespace game_framework;

Ground::Ground(std::pair<int, int> _start, std::pair<int, int> _end) {
	start = _start;
	end = _end;
}
bool Ground::LineSegmentIntersection(pair<pair<int, int>, pair<int, int>> line1, pair<pair<int, int>, pair<int, int>> line2) {
	int o1 = orientation(line1.first, line1.second, line2.first);
	int o2 = orientation(line1.first, line1.second, line2.second);
	int o3 = orientation(line2.first, line2.second, line1.first);
	int o4 = orientation(line2.first, line2.second, line1.second);

	if (o1 != o2 && o3 != o4) {
		return true;
	}

	if (o1 == 0 && onSegment(line1.first, line2.first, line1.second)) {
		return true;
	}

	if (o2 == 0 && onSegment(line1.first, line2.second, line1.second)) {
		return true;
	}

	if (o3 == 0 && onSegment(line2.first, line1.first, line2.second)) {
		return true;
	}

	if (o4 == 0 && onSegment(line2.first, line1.second, line2.second)) {
		return true;
	}

	return false;
}
int Ground::orientation(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
	int val = (q.second - p.second) * (r.first - q.first) -
		(q.first - p.first) * (r.second - q.second);

	if (val == 0) {
		return 0;
	}

	return (val > 0) ? 1 : 2;
}

bool Ground::onSegment(pair<int, int> p, pair<int, int> q, pair<int, int> r) {
	if (q.first <= max(p.first, r.first) && q.first >= min(p.first, r.first) &&
		q.second <= max(p.second, r.second) && q.second >= min(p.second, r.second)) {
		return true;
	}

	return false;
}
int Ground::isOnGround(CMovingBitmap bmp, Ground ground) {
	pair<pair<int, int>, pair<int, int>> CharacterLeftLine = { {bmp.GetLeft(),bmp.GetTop()},{bmp.GetLeft(),bmp.GetTop()+ bmp.GetHeight()} };
	pair<pair<int, int>, pair<int, int>> CharacterTopLine = { {bmp.GetLeft(),bmp.GetTop()},{bmp.GetLeft() + bmp.GetWidth() ,bmp.GetTop() } };
	pair<pair<int, int>, pair<int, int>> CharacterRightLine = { {bmp.GetLeft()+ bmp.GetWidth(),bmp.GetTop()},{bmp.GetLeft() + bmp.GetWidth(),bmp.GetTop() + bmp.GetHeight()} };
	pair<pair<int, int>, pair<int, int>> CharacterBottomLine = { {bmp.GetLeft(),bmp.GetTop()+bmp.GetHeight()},{bmp.GetLeft() + bmp.GetWidth() ,bmp.GetTop() + bmp.GetHeight() } };
	//pair<int, int>ground.start, pair<int, int>ground.end

	pair<pair<int, int>, pair<int, int>> line = { ground.start,ground.end };
	if (LineSegmentIntersection(CharacterLeftLine, line) ||
		LineSegmentIntersection(CharacterRightLine, line) ||
		LineSegmentIntersection(CharacterBottomLine, line)) {
		return 1; 
	}

	return 0; 

}
