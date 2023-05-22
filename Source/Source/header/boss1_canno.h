#pragma once
#include "../../Library/gameutil.h"

class boss1_canno : public Character {
	public:
		boss1_canno(int _x, int _y);
		void Setaction(string _action);
		void init();
		void Move();
		void update();
		void draw();
	private:
		enum class Action {
			MovingDown,Movingup,AttackLow, AttackUp,IDLEUp,IDLEDown
		} action = Action::MovingDown, lastAction = Action::MovingDown;
		int x, y;
		bool position;
		time_t start_AI = clock();
		bool Done=false;
};