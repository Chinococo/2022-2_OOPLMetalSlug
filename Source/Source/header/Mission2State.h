#pragma once
#include "State.h"

class Mission2State : public State {
public:
	virtual void onMove(MapController *mapController) override;
	virtual void onShow(MapController *mapController) override;
};
