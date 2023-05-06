#include "../header/Character.h"

class Soldier : public Character {
public:
	Soldier(int _x, int _y, int _speedX);
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	void attack();
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	void collideWithBullet();
	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	virtual void die() override;
	virtual void draw() override;
	Soldier &operator=(const Soldier &other);
private:
	int velocityY = 0;
	const int JUMP_VELOCITY = -20;
	const int JUMP_COOLDOWN = 2000;
	const int ATTACK_COOLDOWN = 1000;
	bool movingLeft = false;
	bool movingRight = false;
	bool jumping = false;
	bool inAir = false;
	bool lookingUp = false;
	bool attacking = false;
	bool throwingGrenade = false;
	bool pressingDown = false;
	clock_t lastJumpTime = clock();
	clock_t lastAttackTime = clock();
};
