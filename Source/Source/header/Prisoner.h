#pragma once
#include "Character.h"

class Prisoner : public Character {
private:
	const int WANDER_DISTANCE = 50;
	
	int absolutePositionLeft = 0;
	int absolutePositionTop = 0;

	int absoluteAnchorHorizontal = 0;

	int distanceHorizontal = 0;
	int distanceVertical = 0;

	int collisionBoxTweakLeft = 0;
	int collisionBoxTweakTop = 0;

	int collisionBoxWidth = 50;
	int collisionBoxHeight = 90;
	
	int velocityHorizontal = 5;
	int velocityVertical = 0;
	
	bool inAir = false;
	bool animationDone = false;

	std::chrono::time_point<std::chrono::steady_clock> spriteTimer = std::chrono::steady_clock::now();

	Direction lastDirectionHorizontal = Direction::LEFT;
	Direction directionHorizontal = Direction::LEFT;
	Direction directionVertical = Direction::NONE;

	enum class Sprite {
		TIED, RESCUED, MOVE, FALL, REWARD
	} sprite = Sprite::TIED;

	enum class Action {
		TIED, RESCUED, MOVE, FALL, REWARD, LEAVE
	} action = Action::TIED;

	void handleActionTied();
	void handleActionRescued();
	void handleActionMove();
	void handleActionFall();
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

	Prisoner &operator=(const Prisoner &other);

	// For debugging
	int getAbsLeft() const;
	int getAbsTop() const;
	int getAbsFrame();
	int getRelFrame();
	std::string getDirectionHorizontal() const;
	std::string getSprite() const;
	std::string getAction() const;
	bool isAnimationDone() const;
};
