#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "mygame.h"
#include "../Source/header/GameStorage.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	if (state == "map1") {
		marco.update();
		for (auto &soldier : soldiers) {
			soldier.update();
		}
	}
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	background.LoadBitmapByString({ "resources/backgrounds/bg_mainmenu.bmp" }, RGB(0, 0, 0));
	arrow.LoadBitmapByString({ "resources/bmp/arrow.bmp" }, RGB(255, 255, 255));
	background.SetTopLeft(0, 0);
	for (int i = 0; i < 4; i++) {
		CMovingBitmap btn;
		btn.LoadBitmapByString({ "resources/menus/btn_generic.bmp" }, RGB(0, 0, 0));
		btn.SetTopLeft(540, 70 * i + 175);
		mainmenuButtons.push_back(btn);
	}	
	int position[5] = { 185,255,325,400,500 };
	arrow.SetTopLeft(430, position[selectIndex] - 35);
	grounds.push_back(Ground({ 0,450 }, { 460,450 }));
	grounds.push_back(Ground({ 410,450 }, { 410,800 }));
	grounds.push_back(Ground({ 0,550 }, { 1000,550 }));
	grounds.push_back(Ground({ 0,0 }, { 0,600 }));
	grounds.push_back(Ground({ 780,0 }, { 780,600 }));
	ViewPointX = 0;
	ViewPointY = 580;
	std::vector<std::tuple<std::vector<std::string>, std::vector<std::pair<int, int>>, COLORREF>> layer;
	layer.push_back({ {"resources/maps/background2.bmp"},{{3650,330}} , RGB(255, 255, 255) });
	layer.push_back({ {"resources/maps/background1.bmp"},{{3500,330}} , RGB(255, 255, 255) });
	//layer.push_back({ {"resources/maps/test2.bmp"},{{5685,22}} , RGB(0, 0, 0) });//破壞
	//layer.push_back({ {"resources/maps/test1.bmp"},{{5490,15}} , RGB(0, 0, 0) });//破壞
	layer.push_back({ {"resources/maps/map1_1.bmp"},{{0,15}} , RGB(0, 0, 0) });
	//layer.push_back({ {"resources/maps/test0.bmp"},{{5490,15}} , RGB(255, 255, 255) });//原本
	//layer.push_back({ {"resources/maps/test3.bmp"},{{5840,15}} , RGB(255, 255, 255) });//原本
	map.clear();
	for (unsigned i = 0; i < layer.size(); i++) {
		CMovingBitmap temp;
		temp.LoadBitmapByString(std::get<0>(layer[i]), std::get<2>(layer[i]));
		map.push_back({ temp,std::get<1>(layer[i]) });
	}
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	createSoldierGroup();
	marco.init();
	for (auto &soldier : soldiers) {
		soldier.init();
	}
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (state == "init") {
		if (nChar == VK_UP)
			selectIndex = (selectIndex + 4) % 5;
		else if (nChar == VK_DOWN)
			selectIndex = (selectIndex + 1) % 5;
		int position[5] = { 185,255,325,400,500 };
		arrow.SetTopLeft(430, position[selectIndex] - 35);
		if (nChar == VK_RETURN) {
			if (selectIndex == 0) {
				state = "map1";
			}
		}


	}
	else if (state == "map1") {
		if (nChar == VK_RIGHT || nChar == VK_SPACE || nChar == VK_LEFT || nChar == VK_UP|| nChar == VK_DOWN|| nChar == VK_LEFT|| nChar == VK_RIGHT) {
			keydown.insert(nChar);
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	keydown.erase(nChar);
}

void CGameStateRun::OnLButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnLButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnMouseMove(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonDown(UINT nFlags, CPoint point)  // 處理滑鼠的動作
{
}

void CGameStateRun::OnRButtonUp(UINT nFlags, CPoint point)	// 處理滑鼠的動作
{
}

void CGameStateRun::OnShow()
{
	if (state == "init") {
		background.ShowBitmap();
		for (size_t i = 0; i < mainmenuButtons.size(); i++) {
			mainmenuButtons.at(i).ShowBitmap();
		}
		arrow.ShowBitmap();
	}
	else if(state=="map1") {
		
		if (keydown.count(VK_RIGHT))
			ViewPointX -= MapScrollSpeed;
		else if (keydown.count(VK_LEFT) && ViewPointX < 0)
			ViewPointX += MapScrollSpeed;
		for (unsigned i = map.size() - 1;; i--) {
			int now_index = std::get<0>(map[i]).GetFrameIndexOfBitmap();
			std::get<0>(map[i]).SetTopLeft(ViewPointX + std::get<1>(map[i])[now_index].first,
				ViewPointY - background.GetHeight() + std::get<1>(map[i])[now_index].second);
			std::get<0>(map[i]).ShowBitmap();
			if (i == 0)
				break;
		}
		// the latter the object calls draw method, the upper layer it is in
		for (auto &soldier : soldiers) {
			soldier.draw();
		}
		marco.draw();
	}
}
