/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file simulated_sequence.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once
#include <gamelib/input/input.h>
#include <string>
#include <vector>

namespace SenselessSoccer {

/**
 * @brief The JoyStickState enum
 */
enum JoyStickState { STICK_UP, STICK_UP_RIGHT, STICK_RIGHT, STICK_DOWN_RIGHT, STICK_DOWN, STICK_DOWN_LEFT, STICK_LEFT, STICK_UP_LEFT, RESET };

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

    /// frames the input lasts for
    int frames;

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
