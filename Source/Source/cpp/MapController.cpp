#include "stdafx.h"
#include "../header/MapController.h"
#include "../header/Mission1State.h"
#include "../header/Mission2State.h"

MapController::MapController() {
	this->state = new Mission1State();
}

MapController::~MapController() {
	delete this->state;
}

State *MapController::getState(void) {
	return state;
}

void MapController::setState(State *state) {
	this->state = state;
}

void MapController::onMove(void) {
	state->onMove(this);
}

void MapController::onShow(void) {
	state->onShow(this);
}

void MapController::onKeyDown(UINT nChar) {
	state->onKeyDown(this, nChar);
}
