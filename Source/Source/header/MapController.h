#pragma once
#include "State.h"

class MapController {
private:
	State *state;

public:
	MapController();
	~MapController();
	State *getState(void);
	void setState(State *state);
	void handle(void);
};
