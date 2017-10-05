#include "simulate_clearance.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// SimulatedClearance
// ------------------------------------------------------------
SimulatedClearance::SimulatedClearance() {

	// an event to reuse
	ProgrammedEvent evt;

	// press and hold fire
	for (unsigned int i = 0; i < 10; ++i) {
		evt.event_states[GameLib::FIRE_DOWN] = true;
		evt.frames = 5;
		actions.push_back(evt);
	}

	// start pulling back (down) for height
	for (unsigned int i = 0; i < 50; ++i) {
		evt.event_states[GameLib::FIRE_DOWN] = true;
		evt.event_states[GameLib::DOWN] = true;
		evt.frames = 5;
		actions.push_back(evt);
	}
}

} // namespace SenselessSoccer
