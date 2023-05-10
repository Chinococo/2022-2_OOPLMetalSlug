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
		removeInactiveBullets();
		removeInactiveSolider();
		marco.update();
		for (size_t i = 0; i < soldiers.size(); i++) {
			soldiers[i].update();
		}
		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].update();
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
	std::srand(static_cast<unsigned int>(std::time(nullptr)));
	createMap();
	createGrounds();
	createSoldiers();
	marco.init();
	for (size_t i = 0; i < soldiers.size(); i++) {
		soldiers[i].init();
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
				Loading = false;
				
				state = "map1";
			}
		}


	}
	else if (state == "map1") {
		// 0x5A -> Z
		// 0x58 -> X
		if (nChar == VK_LEFT || nChar == VK_RIGHT || nChar == VK_SPACE || nChar == VK_UP|| nChar == VK_DOWN || nChar == 0x5A || nChar == 0x58) {
			keyDowns.insert(nChar);
		}
	}
}

void CGameStateRun::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	keyDowns.erase(nChar);
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
	else if (state == "map1") {
		
		if (keyDowns.count(VK_RIGHT)&&scroll)
			ViewPointX -= MapScrollSpeed;
		//else if (keyDowns.count(VK_LEFT) && ViewPointX < 0)
		//	ViewPointX += MapScrollSpeed;
		updateUnderCharacterLayer();
		updateCharacter();
		updateUpperCharacterLayer();
		if (!Loading) {
			Sleep(1000);
			Loading = true;
		}
		else {
			CDC *pDC = CDDraw::GetBackCDC();
			//game_framework::ChangeFontLog
			CTextDraw::ChangeFontLog(pDC, 25, "微軟正黑體", RGB(0,0,0), 500);
			CString str;
			str.Format(_T("now index=%d x=%d y=%d"), marco.GetFrameIndexOfBitmap(), marco.GetLeft()+abs(ViewPointX), marco.GetTop());

			// 將CString轉換為std::string
			std::string result = CT2A(str);

			CTextDraw::Print(pDC, 0, 0, result);
			CDDraw::ReleaseBackCDC();
		}
		
		
	}
}
