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
 * @file simulated_sequence.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "simulated_sequence.h"

#include <stdio.h>
#include <string.h>

namespace SenselessSoccer {

// ------------------------------------------------------------
// ProgrammedEvent
// ------------------------------------------------------------
ProgrammedEvent::ProgrammedEvent() {
    memset(event_states, 0, sizeof(event_states));
    frames = 0;
}
// ------------------------------------------------------------
// ProgrammedEvent
// ------------------------------------------------------------
void ProgrammedEvent::Reset() { memset(event_states, 0, sizeof(event_states)); }

// ------------------------------------------------------------
// SimulatedAction
// ------------------------------------------------------------
void SimulatedSequence::SimulateAction(
    const JoyStickState &action, bool fire_down,
    int (&event_states)[GameLib::TOTAL_EVENTS]) {
    memset(event_states, 0, sizeof(event_states));
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
