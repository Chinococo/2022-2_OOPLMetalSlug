#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
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
	background.LoadBitmapByString({ "resources/backgrounds/bg_mainmenu.bmp" }, RGB(0, 0, 0));
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
	pharse = "init";
	UpdateArrowPosition();
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
			}
				
		}
			
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
}
void  CGameStateRun::UpdateArrowPosition() {
	int position[5] = { 185,255,325,400,500 };
	arrow.SetTopLeft(430, position[choose]-35);
}
