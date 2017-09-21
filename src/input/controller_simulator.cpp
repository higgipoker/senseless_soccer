#include "controller_simulator.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// ControllerEmulator
// ------------------------------------------------------------
ControllerSimulator::ControllerSimulator(void) {
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void ControllerSimulator::Update() {
	if (current_action->size()) {
		for (int i = 0; i < GameLib::TOTAL_EVENTS; ++i) {
			event_states[i] = current_action->back().event_states[i];
		}
		if (--current_action->back().frames == 0) {
			current_action->pop_back();
		}
	}
}

} // namespace SenselessSoccer
