#include "stdafx.h"
#include "../Core/Resource.h"
#include <mmsystem.h>
#include <ddraw.h>
#include "../Library/audio.h"
#include "../Library/gameutil.h"
#include "../Library/gamecore.h"
#include "../Source/ground.h"
#include <string>
#include "mygame.h"

using namespace game_framework;

/////////////////////////////////////////////////////////////////////////////
// 這個class為遊戲的遊戲執行物件，主要的遊戲程式都在這裡
/////////////////////////////////////////////////////////////////////////////

CGameStateRun::CGameStateRun(CGame *g) : CGameState(g)
{
	// characters
	marco = std::make_unique<CMarco>();
	soldier = std::make_unique<CSoldier>();
}

CGameStateRun::~CGameStateRun()
{
}

void CGameStateRun::OnBeginState()
{
}

void CGameStateRun::OnMove()							// 移動遊戲元素
{
	// apply gravity
	const int VELOCITY_GRAVITY = 5;
	// control movements
	const int MOVE_SPEED = 3;
	const int HANG_TIME_SEC = 10;
	const int VELOCITY_IN_AIR = 5;
	// characters
	// reset dx and dy
	marco->dx = 0;
	marco->dy = 0;
	soldier->dx = 0;
	soldier->dy = 0;
	int JumpDy = 0;
	if (clock() - marco->jumpUpTime < 1000) {
		double t = 500.0/float(clock() - marco->jumpUpTime);
		marco->dy  = marco->dy - (int)t;
	}
		
	if(!marco->isOnGround)//重力
		marco->dy += VELOCITY_GRAVITY ;
	if (!soldier->isOnGround)
		soldier->dy += VELOCITY_GRAVITY;

	if (keydown.count(VK_LEFT)) 
		marco->dx -= MOVE_SPEED;
	if (keydown.count(VK_RIGHT)) 
		marco->dx += MOVE_SPEED;
	
	if (marco->isOnGround && keydown.count(VK_SPACE)) 
		marco->isOnGround = false;
	
	if (Ground::isOverlap(*marco.get(), *ground)) {
		marco->SetFrameIndexOfBitmap(1);
		marco->isOnGround = true;
	}
	else {
		marco->SetFrameIndexOfBitmap(0);
	}

	if (Ground::isOverlap(*soldier.get(), *ground)) {
		soldier->isOnGround = true;
		soldier->SetFrameIndexOfBitmap(1);
	}
	else {
		soldier->SetFrameIndexOfBitmap(0);
	}
	// decide final position
	marco->x += marco->dx;
	marco->y += marco->dy;
	soldier->x += soldier->dx;
	soldier->y += soldier->dy;

	// set finial position
	marco->SetTopLeft(marco->x, marco->y);
	soldier->SetTopLeft(soldier->x, soldier->y);
}

void CGameStateRun::OnInit()  								// 遊戲的初值及圖形設定
{
	pharse = "init";
	LoadPharseElements();
	ground = new Ground(20, 450, 700, 350);
	// characters
	marco->LoadBitmapByString({ "resources/characters/giraffe.bmp", "resources/characters/bee_1.bmp" }, RGB(255, 255, 255));
	marco->x = 300;
	marco->y = 300;
	marco->dx = 0;
	marco->dy = 0;
	marco->jumpUpTime = -99999;
	marco->isOnGround = false;
	soldier->LoadBitmapByString({ "resources/characters/chest.bmp", "resources/characters/ball-ok.bmp" }, RGB(255, 255, 255));
	soldier->x = 500;
	soldier->y = 300;
	soldier->dx = 0;
	soldier->dy = 0;
	soldier->jumpUpTime = clock();
	soldier->isOnGround = false;
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
		if (nChar == VK_LEFT) {
			keydown.insert(nChar);
		}
		if (nChar == VK_UP) {
			keydown.insert(nChar);
		}
		if (nChar == VK_DOWN) {
			keydown.insert(nChar);
		}
		if (nChar == VK_LEFT) {
			keydown.insert(nChar);
		}
		if (nChar == VK_RIGHT) {     
			keydown.insert(nChar);
		}
		if (nChar == VK_SPACE) {
			keydown.insert(nChar);
			marco->jumpUpTime = clock();
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
		ViewPointX = -3600;
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
			temp.LoadBitmapByString(std::get<0>(layer[i]),std::get<2>(layer[i]));
			map.push_back({ temp,std::get<1>(layer[i])});
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
		if (keydown.count(VK_RIGHT))
			ViewPointX -= MapScrollSpeed;
		else if(keydown.count(VK_LEFT)&& ViewPointX<0)
			ViewPointX += MapScrollSpeed;
		for (unsigned i = map.size()-1;; i--) {
			int now_index = std::get<0>(map[i]).GetFrameIndexOfBitmap();
			std::get<0>(map[i]).SetTopLeft(ViewPointX + std::get<1>(map[i])[now_index].first, 
				ViewPointY - background.GetHeight()+ std::get<1>(map[i])[now_index].second);
			std::get<0>(map[i]).ShowBitmap();
			if (i == 0)
				break;
		}
		// characters
		marco->ShowBitmap();
		soldier->ShowBitmap();
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

}
void  CGameStateRun::UpdateArrowPosition() {
	int position[5] = { 185,255,325,400,500 };
	arrow.SetTopLeft(430, position[choose]-35);
}
