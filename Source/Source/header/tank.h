#pragma once
#include "../header/Character.h"
#include "../header/tank_ barrel.h"
class tank : public Character {
public:
	tank(int _x, int _y, int _speedX);
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	void attack();
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	void collideWithBullet();
	virtual void updateAction() override;
	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	virtual void draw() override;
	void dead();
	bool isAttacking();
private:
	bool once = false;
	int velocityY = 0;
	const int JUMP_VELOCITY = -15;
	const int ATTACK_COOLDOWN = 300;
	bool movingLeft = false;
	bool movingRight = false;
	bool jumping = false;
	bool inAir = false;
	bool lookingUp = false;
	bool attacking = false;
	bool knifing = false;
	bool throwingGrenade = false;
	bool pressingDown = false;
	bool nearEnemy = false;
	clock_t lastAttackTime = clock();
	enum class Action {
		IDLE, JUMP,MOVING, SOOTING, Crouch, Crouch_Driving
	} action = Action::IDLE, lastAction = Action::IDLE;
	tank_barrel *barrel;
};