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
	Reset();
	if (current_action->programmed_events.size()) {
		for (int i = 0; i < GameLib::TOTAL_EVENTS; ++i) {
			event_states[i] = current_action->programmed_events.back().event_states[i];
		}
	}
}

} // namespace SenselessSoccer
