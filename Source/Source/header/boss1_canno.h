#pragma once
#include "../../Library/gameutil.h"

class boss1_canno : public Character {
	public:
		boss1_canno(int _x, int _y);
		void Setaction(string _action);
		void init();
		void update();
		void draw();
	private:
		enum class Action {
			IDLE
		} action = Action::IDLE, lastAction = Action::IDLE;
		int x, y;
};