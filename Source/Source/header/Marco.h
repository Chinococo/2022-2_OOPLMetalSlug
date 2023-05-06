#include "../header/Character.h"

class Marco : public Character {
public:
	Marco(int _x, int _y, int _speedX);
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
	virtual void die() override;
	virtual void draw() override;
private:
	int velocityY = 0;
	const int JUMP_VELOCITY = -20;
	const int ATTACK_COOLDOWN = 100;
	bool movingLeft = false;
	bool movingRight = false;
	bool jumping = false;
	bool inAir = false;
	bool lookingUp = false;
	bool attacking = false;
	bool knifing = false;
	bool throwingGrenade = false;
	bool pressingDown = false;
	bool flip = false;
	clock_t lastAttackTime = clock();
	enum class Action {
		IDLE, MOVE, JUMP, LOOK_UP, SHOOT, SHOOT_UP, SHOOT_DOWN, KNIFE, GRENADE, CROUCH_SHOOT, CROUCH_SHOOT_UP, CROUCH_KNIFE, CROUCH_GRENADE, DIE
	} action = Action::IDLE, lastAction = Action::IDLE;
};
