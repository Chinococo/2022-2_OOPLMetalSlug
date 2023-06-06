#pragma once
#include "MapController.h"

class State {
public:
	virtual ~State() = default;
	virtual void onMove(MapController *mapController) = 0;
	virtual void onShow(MapController *mapController) = 0;
};
