#include "../header/Character.h"
#include "Grenade.h"

class Marco : public Character {
public:
	bool isPoweredUp = false;

	Marco(int _x, int _y, int _speedX);
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	void attack();
	void throwGrenade();
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	void collideWithBullet();
	virtual void updateAction() override;
	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	virtual void draw() override;
	void JumpOutDrving(int _x, int _y);
	void dead();
	bool isAttacking();
	void respawn();
	virtual ColBox getColBox(void) override;
	void powerUp(void);
	Marco &operator=(const Marco &other);

private:
	bool once = false;
	int velocityY = 0;
	const int JUMP_VELOCITY = -17;
	const int ATTACK_COOLDOWN = 300;
	const int GRENADE_COOLDOWN = 300;
	const int POWER_UP_DURATION_SEC = 5;
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
	std::chrono::time_point<std::chrono::steady_clock> powerUpTimer = std::chrono::steady_clock::now();
	clock_t lastAttackTime = clock();
	std::chrono::time_point<std::chrono::steady_clock> grenadeTimer = std::chrono::steady_clock::now();
	enum class Action {
		IDLE, MOVE, JUMP, LOOK_UP, SHOOT, SHOOT_UP, SHOOT_DOWN, KNIFE, GRENADE, CROUCH_IDLE, CROUCH_MOVE, CROUCH_SHOOT, CROUCH_KNIFE, CROUCH_GRENADE, DIE
	} action = Action::IDLE, lastAction = Action::IDLE;
};
