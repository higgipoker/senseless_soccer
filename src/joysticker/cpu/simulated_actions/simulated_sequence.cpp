#include "simulated_sequence.h"

#include <stdio.h>
#include <string.h>

namespace SenselessSoccer {

ProgrammedEvent::ProgrammedEvent() {
    memset (event_states, 0, sizeof (event_states));
    milliseconds = 0;
}

void ProgrammedEvent::Reset() {
    memset (event_states, 0, sizeof (event_states));
}

void SimulatedSequence::SimulateAction (const JoyStickState &action, bool fire_down,
                                        int (&event_states) [GameLib::TOTAL_EVENTS]) {
    memset (event_states, 0, sizeof (event_states));
    if (fire_down) {
        event_states[GameLib::FIRE_DOWN] = 1;
    }
    switch (action) {
        case STICK_UP:
            event_states[GameLib::UP] = 1;
            break;
        case STICK_UP_RIGHT:
            event_states[GameLib::UP] = 1;
            event_states[GameLib::RIGHT] = 1;
            break;
        case STICK_RIGHT:
            event_states[GameLib::RIGHT] = 1;
            break;
        case STICK_DOWN_RIGHT:
            event_states[GameLib::DOWN] = 1;
            event_states[GameLib::RIGHT] = 1;
            break;
        case STICK_DOWN:
            event_states[GameLib::DOWN] = 1;
            break;
        case STICK_DOWN_LEFT:
            event_states[GameLib::DOWN] = 1;
            event_states[GameLib::LEFT] = 1;
            break;
        case STICK_LEFT:
            event_states[GameLib::LEFT] = 1;
            break;
        case STICK_UP_LEFT:
            event_states[GameLib::UP] = 1;
            event_states[GameLib::LEFT] = 1;
            break;
    }
}

} // SenselessSoccer
