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
		removeInactives();
		removeInactiveSolider();
		marco.update();
		marco_tank.update();
		for (size_t i = 0; i < rshobus.size(); i++) {
			rshobus[i].update();
		}
		for (size_t i = 0; i < soldiers.size(); i++) {
			soldiers[i].update();
		}
		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].update();
		}
		for (size_t i = 0; i < soldierFireworks.size(); i++) {
			soldierFireworks[i].update();
		}

		boss.update();

		for (size_t i = 0; i < prisoners.size(); i++) {
			prisoners[i].update();
		}

	}
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	boss.init();
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
	createMapObject();
	createPrisoners();
	createRShobus();
	marco.init();
	marco_tank.init();
	for (size_t i = 0; i < soldiers.size(); i++) {
		soldiers[i].init();
	}
	for (size_t i = 0; i < MapObjects.size(); i++) {
		MapObjects[i].init();
	}
	for (size_t i = 0; i < prisoners.size(); i++) {
		prisoners[i].init();
	}
	for (size_t i = 0; i < rshobus.size(); i++) {
		rshobus[i].init();
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
		
		if (keyDowns.count(VK_RIGHT)&&scroll&&!Checkcheckpoint())
			ViewPointX -= MapScrollSpeed;
		if (abs(ViewPointX) < 9500 && abs(ViewPointX) > 8700)
			ViewPointY = static_cast<int>(580 +floor(static_cast<double>(abs(ViewPointX) -8700)/3.8));
		updateUnderCharacterLayer();
		updateMapObject();
		updateCharacter();
		updateUpperCharacterLayer();
		if (!Loading) {
			Sleep(100);
			Loading = true;
		}
		else {
			CDC *pDC = CDDraw::GetBackCDC();
			//game_framework::ChangeFontLog
			CTextDraw::ChangeFontLog(pDC, 25, "微軟正黑體", RGB(0, 0, 0), 500);
			CString str;
			str.Format(_T("marco index=%d, x=%d, y=%d"), marco_tank.GetFrameIndexOfBitmap(), marco.GetLeft()+abs(ViewPointX), marco.GetTop());
			std::string result = CT2A(str);// 將CString轉換為std::string
			CTextDraw::Print(pDC, 0, 0, result);
			
		
			// For debugging
			Prisoner prisoner = prisoners[0];
			char buffer[256]; // 假設你的字串不會超過 256 個字元

			std::snprintf(buffer, sizeof(buffer), "prisoner absLeft=%d, absTop=%d", prisoner.getAbsLeft(), prisoner.getAbsTop());
			std::string str1 = buffer;
			CTextDraw::Print(pDC, 0, 25, str1);

			std::snprintf(buffer, sizeof(buffer), "prisoner action=%s, sprite=%s", prisoner.getAction().c_str(), prisoner.getSprite().c_str());
			str1 = buffer;
			CTextDraw::Print(pDC, 0, 50, str1);

			std::snprintf(buffer, sizeof(buffer), "prisoner directionHorizontal=%s", prisoner.getDirectionHorizontal().c_str());
			str1 = buffer;
			CTextDraw::Print(pDC, 0, 75, str1);

			std::snprintf(buffer, sizeof(buffer), "prisoner absFrame=%d, relFrame=%d", prisoner.getAbsFrame(), prisoner.getRelFrame());
			str1 = buffer;
			CTextDraw::Print(pDC, 0, 100, str1);

			std::snprintf(buffer, sizeof(buffer), "prisoner animationDone=%d", prisoner.isAnimationDone());
			str1 = buffer;
			CTextDraw::Print(pDC, 0, 125, str1);


			CDDraw::ReleaseBackCDC();
		}
		
		for (size_t i = 0; i < prisoners.size(); i++) {
			prisoners[i].draw();
		}
		for (size_t i = 0; i < soldiers.size(); i++) {
			soldiers[i].draw();
		}
		for (size_t i = 0; i < rshobus.size(); i++) {
			rshobus[i].draw();
		}
		boss.draw();
		marco.draw();
		marco_tank.draw();
		for (size_t i = 0; i < bullets.size(); i++) {
			bullets[i].draw();
		}
		for (size_t i = 0; i < soldierFireworks.size(); i++) {
			soldierFireworks[i].draw();
		}
		
	}
}
