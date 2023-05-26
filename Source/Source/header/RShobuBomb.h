#pragma once
#include "Character.h"

class RShobuBomb : public Character {
private:
	int absolutePositionLeft = 0;
	int absolutePositionTop = 0;

	int distanceHorizontal = 0;
	int distanceVertical = 0;

	int collisionBoxTweakLeft = 0;
	int collisionBoxTweakTop = 0;

	int collisionBoxWidth = 50;
	int collisionBoxHeight = 90;

	int velocityHorizontal = 0;
	int velocityVertical = 0;

	bool inAir = false;
	bool animationDone = false;

	std::chrono::time_point<std::chrono::steady_clock> spriteTimer = std::chrono::steady_clock::now();

	Direction directionHorizontal = Direction::LEFT;
	Direction directionVertical = Direction::NONE;

	enum class Sprite {
		MOVE
	} sprite = Sprite::MOVE;

	enum class Action {
		MOVE
	} action = Action::MOVE;

	void handleActionMove();

	void moveVertically(Direction direction);

	bool isCollideWith(Character other);

	void handleGroundCollision();
	void handleWallCollision();

	void switchSprite(Sprite sprite);
	void nextFrame();

public:
	RShobuBomb(int absolutePositionLeft, int absolutePositionTop);

	void init();
	void update();
	void draw();

	RShobuBomb &operator=(const RShobuBomb &other);
};
