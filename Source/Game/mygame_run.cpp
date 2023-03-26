#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include <string>
#include "mygame.h"

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
	
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	pharse = "init";
	LoadPharseElements();
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (pharse == "init") {
		if (nChar == VK_UP)
			choose = (choose + 4) % 5;
		else if (nChar == VK_DOWN)
			choose = (choose + 1) % 5;
		UpdateArrowPosition();

		if (nChar == VK_RETURN) {
			if (choose == 0) {
				clean();
				pharse = "map1";
				LoadPharseElements();
			}
				
		}
			
	}
	else if (pharse == "map1") {
		if (nChar == VK_RIGHT) {
			keydown.insert(nChar);
		}
		else if (nChar == VK_UP) {
			keydown.insert(nChar);
		}
			
	}
	
}
void CGameStateRun::LoadPharseElements() {
	if (pharse == "init") {
		background.LoadBitmapByString({ "resources/backgrounds/bg_mainmenu.bmp"}, RGB(0, 0, 0));
		arrow.LoadBitmapByString({ "resources/bmp/arrow.bmp" }, RGB(255, 255, 255));
		background.SetTopLeft(0, 0);
		for (int i = 0; i < 4; i++) {
			CMovingBitmap btn;
			btn.LoadBitmapByString({ "resources/menus/btn_generic.bmp" }, RGB(0, 0, 0));
			btn.SetTopLeft(540, 70 * i + 175);
			mainmenuButtons.push_back(btn);
		}
		CMovingBitmap btn;
		btn.LoadBitmapByString({ "resources/menus/btn_generic.bmp" }, RGB(0, 0, 0));
		btn.SetTopLeft(540, 495);
		mainmenuButtons.push_back(btn);
		UpdateArrowPosition();
	}
	else if (pharse == "map1") {
		std::vector<std::tuple<CMovingBitmap, int, int>> layer;
		CMovingBitmap temp;
		temp.LoadBitmapByString({"resources/maps/map1_1.bmp" }, RGB(255,255, 255));
		layer.push_back({ temp,0,-30 });

		CMovingBitmap temp1;
		temp1.LoadBitmapByString({ "resources/maps/background1.bmp" }, RGB(255, 255, 255));
		layer.push_back({ temp1,+5200,100 });
		map1 = layer;
	}
}
void CGameStateRun::clean() {
	if (pharse == "init") {
		background.UnshowBitmap();
		for (size_t i = 0; i < mainmenuButtons.size(); i++) {
			mainmenuButtons.at(i).UnshowBitmap();
		}
		arrow.UnshowBitmap();
	}

}
void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	if (pharse == "map1") {
		keydown.erase(nChar);
	}
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
	if (pharse == "init") {
		background.ShowBitmap();
		for (size_t i = 0; i < mainmenuButtons.size(); i++) {
			mainmenuButtons.at(i).ShowBitmap();
		}
		show_text_by_phase();
		arrow.ShowBitmap();
	}
	else if (pharse == "map1") {
		if (keydown.count(VK_RIGHT)&&background.GetWidth()-600)
			Map1X -= MapScrollSpeed;
		//if (keydown.count(VK_UP))
		//	Map1Y += MapScrollSpeed;
		for (unsigned i = map1.size()-1;; i--) {
			std::get<0>(map1[i]).SetTopLeft(Map1X+ std::get<1>(map1[i]), Map1Y - background.GetHeight()+ std::get<2>(map1[i]));
			std::get<0>(map1[i]).ShowBitmap();
			if (i == 0)
				break;
		}
		//show_text_by_phase();
	}
	
}
void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();
	if (pharse == "init") {
		CTextDraw::ChangeFontLog(pDC, 21, "Arial", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, 560, 185, "This is Test1");
		CTextDraw::Print(pDC, 560, 255, "This is Test2");
		CTextDraw::Print(pDC, 560, 325, "This is Test3");
		CTextDraw::Print(pDC, 560, 400, "This is Test4");
		CTextDraw::Print(pDC, 560, 500, "This is Test5");
		CDDraw::ReleaseBackCDC();
	}
	else if (pharse == "map1") {
		CTextDraw::ChangeFontLog(pDC, 21, "Arial", RGB(255, 255, 255), 800);
		CTextDraw::Print(pDC, 560, 185, to_string(Map1X));
		CTextDraw::Print(pDC, 560, 255, to_string(Map1Y));
	}

}
void  CGameStateRun::UpdateArrowPosition() {
	int position[5] = { 185,255,325,400,500 };
	arrow.SetTopLeft(430, position[choose]-35);
}
