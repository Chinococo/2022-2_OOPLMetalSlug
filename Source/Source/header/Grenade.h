#pragma once
#include <chrono>

class Grenade : public Character {
private:
	int absolutePositionLeft = 0;
	int absolutePositionTop = 0;
	int distanceHorizontal = 20;
	int distanceVertical = -20;
	int velocityHorizontal = 20;
	int velocityVertical = -30;
	bool dying = false;
	bool animationDone = false;
	Direction directionHorizontal = Direction::RIGHT;
	Direction lastDirectionHorizontal = Direction::RIGHT;
	std::chrono::time_point<std::chrono::steady_clock> spawnTime = std::chrono::steady_clock::now();
	enum class Sprite {
		MOVE, EXPLODE
	} sprite = Sprite::MOVE;
	enum class Action {
		MOVE, EXPLODE
	} action = Action::MOVE;

	void handleActionMove(void);
	void handleActionExplode(void);
	void handleGroundCollision(void);
	void switchSprite(Sprite sprite);
	void nextFrame(void);

public:
	Grenade(int absolutePositionLeft, int absolutePositionTop, Direction directionHorizonal);

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
	bool isExpired(void) const;
	ColBox explode(void);
	virtual ColBox getColBox(void) override;
};
