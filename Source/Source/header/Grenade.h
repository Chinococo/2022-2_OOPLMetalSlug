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
	Direction directionHorizontal = Direction::RIGHT;
	std::chrono::time_point<std::chrono::steady_clock> spawnTime = std::chrono::steady_clock::now();

	void handleGroundCollision(void);
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
