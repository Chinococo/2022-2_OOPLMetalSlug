#pragma once
#include "Character.h"

enum class Direction {
	LEFT, RIGHT, UP, DOWN
};

class Prisoner : public Character {
private:
	const int WANDER_DISTANCE = 200;
	
	int anchoredX = 0;
	
	int velocityX = 2;
	int velocityY = 0;
	
	bool inAir = false;
	bool once = true;
	
	enum class Sprite {
		TIED, RESCUED, MOVE, FALL, REWARD
	} sprite = Sprite::TIED;

	enum class Action {
		TIED, RESCUED, MOVE, REWARD, LEAVE
	} action = Action::TIED;

	Direction direction = Direction::RIGHT;

	void handleTied();
	void handleRescued();
	void handleMove();
	void handleReward();
	void handleLeave();

	virtual void moveLeftRight() override;
	void fall();

	virtual void collideWithGround() override;
	virtual void collideWithWall() override;
	void collideWithBorder();

	virtual void changeAnimation() override;
	virtual void updateAnimation() override;
	
public:
	Prisoner(int x, int y);
	
	virtual void init() override;
	virtual void update() override;
	virtual void draw() override;

	// For debugging
	std::string getAction() const;
};
