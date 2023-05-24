#pragma once
#include "../../Library/gameutil.h"
#include "../header/Boss1_laser.h"
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
			MovingDown,Movingup,AttackLow, AttackUp, IDLEDown,IDLEUp,LasetLow,LaserUp
		} action = Action::LaserUp, lastAction = Action::LaserUp;
		int x, y;
		bool position;
		time_t start_AI = clock();
		bool Done=false;
		Boss1_laser *laser;
};