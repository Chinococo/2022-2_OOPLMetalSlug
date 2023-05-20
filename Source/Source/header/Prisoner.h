#pragma once
#include "Character.h"

class Prisoner : public Character {
private:
	const int WANDER_RANGE = 200;
	int anchoredX = 0;
	int anchoredY = 0;
	int velocityX = 2;
	int velocityY = 0;
	bool inAir = false;
	bool once = true;
	std::string direction = "left";
	enum class Sprite {
		TIED, RESCUED, MOVE, FALL, REWARD
	} sprite = Sprite::TIED;
	enum class Action {
		TIED, RESCUED, MOVE, REWARD, LEAVE
	} action = Action::TIED;

public:
	Prisoner(int x, int y);
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
	void collideWithBorder();
	virtual void draw() override;
	// Main action logic
	void handleTied();
	void handleRescued();
	void handleMove();
	void handleReward();
	void handleLeave();
};
