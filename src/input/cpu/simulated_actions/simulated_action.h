#pragma once
#include <gamelib/input/input.h>
#include <vector>

namespace SenselessSoccer {

/**
 * @brief a programmed event
 */
struct ProgrammedEvent {

    /**
     * @brief ProgrammedEvent
     */
    ProgrammedEvent() {
        for(unsigned int i = 0; i < GameLib::TOTAL_EVENTS; ++i) {
            event_states[i] = false;
        }

        frames = 0;
    }

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
    /// a list of events, one per frame
    std::vector<ProgrammedEvent> actions;
};

} // SenselessSoccer
