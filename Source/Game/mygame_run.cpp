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
	bg_mainmenu.LoadBitmapByString({ "resources/backgrounds/bg_mainmenu.bmp" }, RGB(0, 0, 0));
	bg_mainmenu.SetTopLeft(0, 0);
	for (int i = 0; i < 4; i++) {
		CMovingBitmap btn;
		btn.LoadBitmapByString({ "resources/menus/btn_generic.bmp" }, RGB(0, 0, 0));
		btn.SetTopLeft(540, 70 * i + 175);
		btns_mainmenu.push_back(btn);
	}
	CMovingBitmap btn;
	btn.LoadBitmapByString({ "resources/menus/btn_generic.bmp" }, RGB(0, 0, 0));
	btn.SetTopLeft(540, 495);
	btns_mainmenu.push_back(btn);
}

void CGameStateRun::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	
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
	bg_mainmenu.ShowBitmap();
	for (size_t i = 0; i < btns_mainmenu.size(); i++) {
		btns_mainmenu.at(i).ShowBitmap();
	}
	show_text_by_phase();
}

void CGameStateRun::show_text_by_phase() {
	CDC *pDC = CDDraw::GetBackCDC();

	CTextDraw::ChangeFontLog(pDC, 21, "微軟正黑體", RGB(0, 0, 0), 800);

	if (phase == 1 && sub_phase == 1) {
		CTextDraw::Print(pDC, 237, 128, "修改你的主角！");
		CTextDraw::Print(pDC, 55, 163, "將灰色方格換成 resources 內的 giraffe.bmp 圖樣！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 2 && sub_phase == 1) {
		CTextDraw::Print(pDC, 26, 128, "下一個階段，讓長頸鹿能夠透過上下左右移動到這個位置！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 3 && sub_phase == 1) {
		CTextDraw::Print(pDC, 205, 128, "幫你準備了一個寶箱");
		CTextDraw::Print(pDC, 68, 162, "設計程式讓長頸鹿摸到寶箱後，將寶箱消失！");
		CTextDraw::Print(pDC, 68, 196, "記得寶箱要去背，使用 RGB(255, 255, 255)");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 4 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了一個蜜蜂好朋友");
		CTextDraw::Print(pDC, 89, 162, "已經幫它做了兩幀的動畫，讓它可以上下移動");
		CTextDraw::Print(pDC, 110, 196, "寫個程式來讓你的蜜蜂好朋友擁有動畫！");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 5 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了三扇門");
		CTextDraw::Print(pDC, 89, 162, "設計程式讓長頸鹿摸到門之後，門會打開");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (phase == 6 && sub_phase == 1) {
		CTextDraw::Print(pDC, 173, 128, "幫你準備了一顆會倒數的球");
		CTextDraw::Print(pDC, 89, 162, "設計程式讓球倒數，然後顯示 OK 後停止動畫");
		CTextDraw::Print(pDC, 373, 537, "按下 Enter 鍵來驗證");
	}
	else if (sub_phase == 2) {
		CTextDraw::Print(pDC, 268, 128, "完成！");
	}

	CDDraw::ReleaseBackCDC();
}