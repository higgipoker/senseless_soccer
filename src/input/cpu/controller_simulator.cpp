#include "controller_simulator.h"
#include "simulated_actions/simulated_action.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// ControllerEmulator
// ------------------------------------------------------------
ControllerSimulator::ControllerSimulator(void) {
	current_action = new SimulateNothing();
}

// ------------------------------------------------------------
// ~ControllerSimulator
// ------------------------------------------------------------
ControllerSimulator::~ControllerSimulator() {
	delete current_action;
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void ControllerSimulator::Update() {
	// to track if fire down has changed, save state before base update
	int prev_fire_state = event_states[GameLib::FIRE_DOWN];

	this->Reset();

	if (current_action->actions.size()) {
		for (int i = 0; i < GameLib::TOTAL_EVENTS; ++i) {
			event_states[i] = current_action->actions.back().event_states[i];
		}
		if (--current_action->actions.back().frames == 0) {
			current_action->actions.pop_back();
		}
	}

	if (prev_fire_state) {
		if (event_states[GameLib::FIRE_DOWN] == 0) {
			fire_timer.restart();
			event_states[GameLib::FIRE_DOWN] = 1;
		} else {
			event_states[GameLib::FIRE_LENGTH] = fire_timer.getElapsedTime().asMilliseconds();
		}
	} else if (event_states[GameLib::FIRE_DOWN] == 1) {
		event_states[GameLib::FIRE_UP] = 1;
		event_states[GameLib::FIRE_DOWN] = 0;
		event_states[GameLib::FIRE_LENGTH_CACHED] = fire_timer.getElapsedTime().asMilliseconds();
		event_states[GameLib::FIRE_LENGTH] = 0;
	}

	if (prev_fire_state) {
		if (event_states[GameLib::FIRE_UP]) {
			Notify(ControllerEvent(FIRE_RELEASE, event_states[GameLib::FIRE_LENGTH_CACHED]));
		}

	} else {
		if (event_states[GameLib::FIRE_DOWN]) {
			Notify(ControllerEvent(FIRE_PRESS));
		}
	}
}

} // namespace SenselessSoccer
