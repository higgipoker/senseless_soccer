#include "simulate_nothing.h"
#include <algorithm>
namespace SenselessSoccer {

// ------------------------------------------------------------
// SimulatedClearance
// ------------------------------------------------------------
SimulateNothing::SimulateNothing() {

    // stick down and right
    ProgrammedEvent evt1;
    SimulatedSequence::SimulateAction (STICK_DOWN_RIGHT, false, evt1.event_states);
    evt1.milliseconds = 5000;
    evt1.id = "DOWN RIGHT";
    actions.push_back (evt1);

    // stick down
    ProgrammedEvent evt2;
    SimulatedSequence::SimulateAction (STICK_DOWN, false, evt2.event_states);
    evt2.milliseconds = 3000;
    evt2.id = "DOWN";
    actions.push_back (evt2);

    // stick down and fire down
    ProgrammedEvent evt3;
    SimulatedSequence::SimulateAction (STICK_DOWN, true, evt3.event_states);
    evt3.milliseconds = 200;
    evt3.id = "DOWN FIRE_PRESS";
    actions.push_back (evt3);

    // stick down and fire up
    ProgrammedEvent evt4;
    SimulatedSequence::SimulateAction (STICK_DOWN, false, evt4.event_states);
    evt4.milliseconds = 400;
    evt4.id = "DOWN FIRE_RELEASE";
    actions.push_back (evt4);

    // reverse the order
    std::reverse (actions.begin(), actions.end());
}

} // namespace SenselessSoccer
