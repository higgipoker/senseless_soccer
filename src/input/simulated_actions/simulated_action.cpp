#include "simulated_action.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Tick
// ------------------------------------------------------------
void SimulatedAction::Tick(void) {
	programmed_events.pop_back();
}

} // SenselessSoccer
