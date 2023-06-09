#pragma once
#include "State.h"

class FinishState : public State {
public:
	virtual void onMove(MapController *mapController) override;
	virtual void onShow(MapController *mapController) override;
	virtual void onKeyDown(MapController *mapController, UINT nChar) override;
};
