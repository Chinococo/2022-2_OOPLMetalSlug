#pragma once
#include "../header/Character.h"
#include "../header/tank_ barrel.h"
#include "../header/tank_bullet.h"
class tank : public Character {
public:
	tank(int _x, int _y, int _speedX);
	~tank();
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	void attack();
	void increaseX(int increse);
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	void collideWithBullet();
	virtual void updateAction() override;
	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	virtual void draw() override;
	void take_in();
	void take_out();
	void dead();
	bool isAttacking();
	void respawn(void);
	tank &operator=(const tank &other);
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
	bool out = false;
	clock_t lastAttackTime = clock();
	clock_t roate = clock();
	clock_t out_drviing = clock();
	clock_t in_driving = clock();
	bool drving = false;
	enum class Action {
		IDLE, JUMP,MOVING, SOOTING, Crouch, Crouch_Driving
	} action = Action::IDLE, lastAction = Action::IDLE;
	tank_barrel *barrel;
};
