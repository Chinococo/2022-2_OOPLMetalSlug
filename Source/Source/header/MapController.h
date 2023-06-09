#pragma once

class State;

class MapController {
private:
	State *state;

public:
	MapController();
	~MapController();
	State *getState(void);
	void setState(State *state);
	void onMove(void);
	void onShow(void);
	void onKeyDown(UINT nChar);
};
