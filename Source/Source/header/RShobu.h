#pragma once
#include "Character.h"
#include <chrono>

class RShobu : public Character {
private:
	const int DISTANCE_TO_HERO_HORIZONTAL = 30;
	const int DISTANCE_TO_HERO_VERTICAL = 100;

	int health = 20;

	int absolutePositionLeft = 0;
	int absolutePositionTop = 0;

	int distanceHorizontal = 0;
	int distanceVertical = 0;

	int collisionBoxTweakLeft = 0;
	int collisionBoxTweakTop = 0;

	int collisionBoxWidth = 100;
	int collisionBoxHeight = 90;

	int velocityHorizontal = 12;
	int velocityVertical = 0;

	bool animationDone = false;

	std::chrono::time_point<std::chrono::steady_clock> spriteTimer = std::chrono::steady_clock::now();

	Direction directionHorizontal = Direction::LEFT;
	Direction directionVertical = Direction::NONE;

	enum class Sprite {
		MOVE, DIE
	} sprite = Sprite::MOVE;

	enum class Action {
		MOVE, DIE
	} action = Action::MOVE;

	void handleActionChase();
	void handleActionMove();
	void handleActionDie();

	void moveHorizontally(Direction direction);
	void moveVertically(Direction direction);

	bool isCollideWith(Character other);

	void handleWallCollision();

	void switchSprite(Sprite sprite);
	void nextFrame();

public:
	RShobu(int absolutePositionLeft, int absolutePositionTop);

	void init();
	void update();
	void draw();

	RShobu &operator=(const RShobu &other);

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
