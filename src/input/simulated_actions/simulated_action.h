#pragma once
#include <gamelib/input/input.h>
#include <vector>

namespace SenselessSoccer {

/** @brief a programmed event */
struct ProgrammedEvent {

	/// status of each input
	int event_states[GameLib::TOTAL_EVENTS];

	/// frames the input lasts for
	int frames;
};

/**
 * @brief The SimulatedAction class
 */
class SimulatedAction {
  public:
	/**
	 * @brief one frame
	 */
	void Tick();

	/// a list of events, one per frame
	std::vector<ProgrammedEvent> programmed_events;
};

} // SenselessSoccer
