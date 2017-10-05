#include "simulate_nothing.h"
#include <algorithm>
namespace SenselessSoccer {

// ------------------------------------------------------------
// SimulatedClearance
// ------------------------------------------------------------
SimulateNothing::SimulateNothing() {
	ProgrammedEvent evt1;
	evt1.event_states[GameLib::DOWN] = true;
	evt1.event_states[GameLib::RIGHT] = true;
	evt1.frames = 500;
	actions.push_back(evt1);

	ProgrammedEvent evt2;
	evt2.event_states[GameLib::DOWN] = true;
	evt2.frames = 100;
	actions.push_back(evt2);

	ProgrammedEvent evt3;
	evt3.event_states[GameLib::DOWN] = true;
	evt3.event_states[GameLib::FIRE_DOWN] = true;
	evt3.frames = 40;
	actions.push_back(evt3);

	ProgrammedEvent evt4;
	evt4.event_states[GameLib::DOWN] = true;
	evt4.event_states[GameLib::FIRE_UP] = true;
	evt4.frames = 40;
	actions.push_back(evt4);

	ProgrammedEvent evt5;
	evt5.event_states[GameLib::DOWN] = true;
	evt5.frames = 120;
	actions.push_back(evt5);

	std::reverse(actions.begin(), actions.end());
}

} // namespace SenselessSoccer
