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

        // log when the action changes
        if (log) {
            std::cout << current_sequence->actions.back().id << std::endl;
            log = false;
        }

        // this is the first action in a sequence (so start timer)
        if (first_action) {
            ticks = 0;
            first_action = false;
        }

        // to track if fire down has changed, save state before base update
        int prev_fire_state = event_states[GameLib::FIRE_DOWN];

        // reset all inputs back to 0
        Reset();

        // copy the simulated actions to live event states
        for (int i = 0; i < GameLib::TOTAL_EVENTS; ++i) {
            event_states[i] = current_sequence->actions.back().event_states[i];
        }

        // end of current action?
        if (++ticks >= current_sequence->actions.back().frames) {
            ticks = 0;
            current_sequence->actions.pop_back();
            Reset();
            log = true;
        }

        // fire press lenght
        if (event_states[GameLib::FIRE_DOWN]) {
            event_states[GameLib::FIRE_LENGTH] =
                fire_timer.getElapsedTime().asMilliseconds();
        }

        // check for fire pressed event
        if (prev_fire_state == 0) {
            if (event_states[GameLib::FIRE_DOWN]) {
                fire_timer.restart();
                Notify(FIRE_PRESS);
            }
        }

        // check for fire release
        else {
            if (event_states[GameLib::FIRE_DOWN] == 0) {

                // set the fire timer
                event_states[GameLib::FIRE_LENGTH_CACHED] =
                    fire_timer.getElapsedTime().asMilliseconds();

                // notify observers of controller event
                Notify(ControllerEvent(
                    FIRE_RELEASE, event_states[GameLib::FIRE_LENGTH_CACHED]));
            }
        }
    } else {
        if (log) {
            std::cout << "RELEASE ALL" << std::endl;
            log = false;
        }
    }
}

} // namespace SenselessSoccer
