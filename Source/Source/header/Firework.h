#pragma once
#include "Character.h"

class Firework : public Character {
private:
	std::string direction;
	int velocityX = 3;
	int velocityY = 0;
	enum class Action {
		MOVE, DIE
	} action, lastAction;

public:
	Firework(int x, int y, std::string direction);
	virtual void init() override;
	virtual void update() override;
	virtual void control() override;
	virtual void move() override;
	virtual void moveLeftRight() override;
	virtual void jumpAndFall() override;
	virtual void updateAction() override;
	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	void collideWithHero();
	virtual void draw() override;
};
