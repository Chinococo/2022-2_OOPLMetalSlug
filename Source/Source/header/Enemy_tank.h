#pragma once
#include "../header/Character.h"

class Enemy_tank : public Character {
public:
	Enemy_tank(int _x, int _y, int _speedX);
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	void attack();
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	void dead();
	void collideWithBullet();
	virtual void updateAction() override;
	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	virtual void draw() override;
	Enemy_tank &operator=(const Enemy_tank &other);
	virtual ColBox getColBox(void) override;
	void reset(void);

private:
	bool once = true;
	int velocityY = 0;
	const int JUMP_VELOCITY = -15;
	const int JUMP_COOLDOWN = 2000;
	const int ATTACK_COOLDOWN = 10000;
	bool movingLeft = false;
	bool movingRight = false;
	bool jumping = false;
	bool inAir = false;
	bool lookingUp = false;
	bool attacking = false;
	bool nearEnemy = false;
	bool throwingGrenade = false;
	bool pressingDown = false;
	clock_t lastJumpTime = clock();
	clock_t lastAttackTime = clock();
	enum class Action {
		IDLE, MOVE, JUMP, FIREWORK, GRENADE, BOMB, DIE
	} action = Action::IDLE, lastAction = Action::IDLE;
};
