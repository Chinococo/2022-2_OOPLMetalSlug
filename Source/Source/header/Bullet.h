#include "../header/Character.h"

class Bullet : public Character {
public:
	Bullet(int _x, int _y, int _facingX, std::string _owner);
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
	bool isAlive() const;
	std::string owner;
};
