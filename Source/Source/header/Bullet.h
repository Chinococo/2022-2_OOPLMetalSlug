#include "../header/Character.h"

class Bullet : public Character {
public:
	Bullet(int _x, int _y, int _speedX, int _facingX, int _facingY, std::string _owner);
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	void collideWithCharacter();
	virtual void updateAction() override;
	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	virtual void die() override;
	virtual void draw() override;
	Bullet &Bullet::operator=(const Bullet &other);
	std::string owner;
};