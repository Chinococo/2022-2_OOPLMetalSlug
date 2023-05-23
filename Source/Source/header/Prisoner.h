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

	int collisionBoxWidth = 0;
	int collisionBoxHeight = 0;
	
	int velocityHorizontal = 5;
	int velocityVertical = 0;
	
	bool inAir = false;
	bool animationDone = false;

	Direction currentDirectionHorizontal = Direction::LEFT;

	enum class Sprite {
		TIED, RESCUED, MOVE, FALL, REWARD
	} currentSprite = Sprite::TIED;

	enum class Action {
		TIED, RESCUED, MOVE, REWARD, LEAVE
	} currentAction = Action::TIED;

	void handleActionTied();
	void handleActionRescued();
	void handleActionMove();
	void handleActionReward();
	void handleActionLeave();

	void moveHorizontally(Direction direction);
	void moveVertically(Direction direction);

	bool isCollideWith(Marco marco);
	bool isCollideWith(Bullet bullet);

	void handleGroundCollision();
	void handleWallCollision();
	void handleBorderCollision();

	void switchSprite(Sprite sprite);
	void nextFrame();
	
public:
	Prisoner(int left, int top);
	
	void init();
	void update();
	void draw();

	// For debugging
	std::string getSprite() const;
	std::string getAction() const;
};
