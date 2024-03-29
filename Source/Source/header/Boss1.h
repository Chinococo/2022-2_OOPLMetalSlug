#pragma once
#include "../header/Character.h"
#include "../header/boss1_canno.h"
class Boss1 : public Character {
public:
	Boss1(int _x, int _y);
	virtual void init() override;
	void damge(int damge);
	virtual void update() override;
	virtual void draw() override;
	/*
	virtual void control() override;
	virtual void move() override;
	void attack();
	void collideWithBullet();
	virtual void updateAction() override;
	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	*/
private:
	int x;
	int y;
	boss1_canno* canno;
	int hp = 20;
	int now_hp = 20;
	enum class Action {
		IDLE
	} action = Action::IDLE, lastAction = Action::IDLE;
};
