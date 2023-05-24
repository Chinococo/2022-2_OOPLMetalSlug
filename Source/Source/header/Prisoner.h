#pragma once
#include "Character.h"

enum class Direction {
	LEFT, RIGHT, UP, DOWN
};

class Prisoner : public Character {
private:
	const int WANDER_DISTANCE = 200;
	
	int absolutePositionLeft = 0;
	int absolutePositionTop = 0;

	int absoluteAnchorHorizontal = 0;

	int distanceHorizontal = 0;
	int distanceVertical = 0;

	int collisionBoxTweakLeft = 0;
	int collisionBoxTweakTop = 0;

	int collisionBoxWidth = 30;
	int collisionBoxHeight = 90;
	
	int velocityHorizontal = 5;
	int velocityVertical = 0;
	
	bool inAir = false;
	bool animationDone = false;

	std::chrono::time_point<std::chrono::steady_clock> spriteTimer = std::chrono::steady_clock::now();

	Direction directionHorizontal = Direction::LEFT;

	enum class Sprite {
		TIED, RESCUED, MOVE, FALL, REWARD
	} sprite = Sprite::TIED;

	enum class Action {
		TIED, RESCUED, MOVE, REWARD, LEAVE
	} action = Action::TIED;

	void handleActionTied();
	void handleActionRescued();
	void handleActionMove();
	void handleActionReward();
	void handleActionLeave();

	void moveHorizontally(Direction direction);
	void moveVertically(Direction direction);

	bool isCollideWith(Character other);

	void handleGroundCollision();
	void handleWallCollision();

	void switchSprite(Sprite sprite);
	void nextFrame();
	
public:
	Prisoner(int absolutePositionLeft, int absolutePositionTop);
	
	void init();
	void update();
	void draw();

	// For debugging
	/*
	int getAbsIndex();
	int getRelIndex();
	*/
	std::string getSprite() const;
	std::string getAction() const;
	/*
	bool isAnimationDone() const;
	*/
};
