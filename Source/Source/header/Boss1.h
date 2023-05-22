#pragma once
#include "../header/Character.h"

class Boss1 : public Character {
public:
	Boss1(int _x, int _y);
	virtual void init() override;
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
	enum class Action {
		IDLE
	} action = Action::IDLE, lastAction = Action::IDLE;
};
