#include "../header/Character.h"

class Marco : public Character {
public:
	Marco(int _x, int _y);
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	virtual void collideWithBullet() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	virtual void draw() override;
private:
	clock_t lastJumpTime = clock();
	int velocityY = 0;
	bool movingLeft = false;
	bool movingRight = false;
	bool jumping = false;
	bool inAir = false;
	bool lookingUp = false;
	bool pressDown = false;
	bool shooting = false;
};
