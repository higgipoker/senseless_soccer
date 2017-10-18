#pragma once
#include <gamelib/input/input.h>
#include <string>
#include <vector>

namespace SenselessSoccer {

enum JoyStickState {
    STICK_UP,
    STICK_UP_RIGHT,
    STICK_RIGHT,
    STICK_DOWN_RIGHT,
    STICK_DOWN,
    STICK_DOWN_LEFT,
    STICK_LEFT,
    STICK_UP_LEFT
};

/**
 * @brief a programmed event
 */
struct ProgrammedEvent {

    /**
     * @brief ProgrammedEvent
     */
    ProgrammedEvent();

    /**
     * @brief Reset
     */
    void Reset();

    /// status of each input
    int event_states[GameLib::TOTAL_EVENTS];

    /// ms the input lasts for
    int milliseconds;

    /// string id for debugging
    std::string id;
};

/**
 * @brief The SimulatedAction class
 */
class SimulatedSequence {
  public:
    /// a list of events, one per frame
    std::vector<ProgrammedEvent> actions;

    /**
     * @brief helper
     * @param action
     */
    static void SimulateAction(const JoyStickState &action, bool fire_down, int (&event_states)[GameLib::TOTAL_EVENTS]);
};

} // SenselessSoccer
