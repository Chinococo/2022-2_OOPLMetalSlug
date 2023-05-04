#include "../header/Character.h"

class Marco : public Character {
public:
	Marco(int _x, int _y, int _speedX);
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	void shoot();
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	void collideWithBullet();
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	virtual void die() override;
	virtual void draw() override;
private:
	clock_t lastShootTime = clock();
	int velocityY = 0;
	const int SHOOT_COOLDOWN = 1000;
	bool movingLeft = false;
	bool movingRight = false;
	bool jumping = false;
	bool inAir = false;
	bool lookingUp = false;
	bool pressDown = false;
	bool shooting = false;
};
