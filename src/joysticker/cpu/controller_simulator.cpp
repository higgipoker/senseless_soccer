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
 * @file controller_simulator.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "controller_simulator.h"
#include "simulated_actions/simulated_sequence.h"
#include <iostream>

namespace SenselessSoccer {

// ------------------------------------------------------------
// ControllerEmulator
// ------------------------------------------------------------
ControllerSimulator::ControllerSimulator(void) {
    current_sequence = new SimulateNothing();
    first_action = true;
}

// ------------------------------------------------------------
// ~ControllerSimulator
// ------------------------------------------------------------
ControllerSimulator::~ControllerSimulator() { delete current_sequence; }

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void ControllerSimulator::Update() {

    // if there is an action in the list
    if (current_sequence->actions.size()) {

        // this is the first action in a sequence (so start timer)
        if (first_action) {
            ticks = 0;
            first_action = false;
        }

        // track changes
        int old_states[GameLib::TOTAL_EVENTS] = {event_states[0], event_states[1], event_states[2], event_states[3], event_states[4], event_states[5],
                                                 event_states[6], event_states[7], event_states[8], event_states[9], event_states[10]};

        // reset all inputs back to 0
        Reset();

        // copy the simulated actions to live event states
        for (unsigned int i = 0; i < GameLib::TOTAL_EVENTS; ++i) {
            event_states[i] = current_sequence->actions.back().event_states[i];
        }

        // end of current action?
        if (++ticks >= current_sequence->actions.back().frames) {
            ticks = 0;
            current_sequence->actions.pop_back();
        }

        // fire press lenght
        if (event_states[GameLib::FIRE_DOWN]) {
            event_states[GameLib::FIRE_LENGTH] = fire_timer.getElapsedTime().asMilliseconds();
        }

        // FIRE
        if (!old_states[GameLib::FIRE_DOWN]) {
            if (event_states[GameLib::FIRE_DOWN]) {
                fire_timer.restart();
                Notify(ControllerEvent(FIRE, PRESSED));
            }
        } else {
            if (!event_states[GameLib::FIRE_DOWN]) {

                // set the fire timer
                event_states[GameLib::FIRE_LENGTH_CACHED] = fire_timer.getElapsedTime().asMilliseconds();

                // notify observers of controller event
                Notify(ControllerEvent(FIRE, RELEASED, event_states[GameLib::FIRE_LENGTH_CACHED]));
            }
        }

        // LEFT
        if (!old_states[GameLib::LEFT]) {
            if (event_states[GameLib::LEFT]) {
                Notify(ControllerEvent(DPAD_LEFT, PRESSED));
            }
        } else {
            if (!event_states[GameLib::LEFT]) {
                Notify(ControllerEvent(DPAD_LEFT, RELEASED));
            }
        }

        // RIGHT
        if (!old_states[GameLib::RIGHT]) {
            if (event_states[GameLib::RIGHT]) {
                Notify(ControllerEvent(DPAD_RIGHT, PRESSED));
            }
        } else {
            if (!event_states[GameLib::RIGHT]) {
                Notify(ControllerEvent(DPAD_RIGHT, RELEASED));
            }
        }

        // UP
        if (!old_states[GameLib::UP]) {
            if (event_states[GameLib::UP]) {
                Notify(ControllerEvent(DPAD_UP, PRESSED));
            }
        } else {
            if (!event_states[GameLib::UP]) {
                Notify(ControllerEvent(DPAD_UP, RELEASED));
            }
        }

        // DOWN
        if (!old_states[GameLib::DOWN]) {
            if (event_states[GameLib::DOWN]) {
                Notify(ControllerEvent(DPAD_DOWN, PRESSED));
            }
        } else {
            if (!event_states[GameLib::DOWN]) {
                Notify(ControllerEvent(DPAD_DOWN, RELEASED));
            }
        }
    }
}

} // namespace SenselessSoccer
