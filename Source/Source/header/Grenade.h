#pragma once
#include <chrono>

class Grenade : public Character {
private:
	int absolutePositionLeft = 0;
	int absolutePositionTop = 0;
	int distanceHorizontal = 0;
	int distanceVertical = 0;
	int velocityHorizontal = 20;
	int velocityVertical = -15;
	Direction directionHorizontal = Direction::RIGHT;
	std::chrono::time_point<std::chrono::steady_clock> spawnTime = std::chrono::steady_clock::now();

	void explode(void);
	void handleGroundCollision(void);
	void nextFrame(void);

public:
	Grenade(int absolutePositionLeft, int absolutePositionTop, Direction directionHorizonal);

	virtual void init(void) override;
	virtual void update(void) override;
	virtual void draw(void) override;
};
