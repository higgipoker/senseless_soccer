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
 * @file simulate_nothing.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "simulate_nothing.h"
#include <algorithm>
namespace SenselessSoccer {

// ------------------------------------------------------------
// SimulateNothing
// ------------------------------------------------------------
SimulateNothing::SimulateNothing() {

    // stick down and right
    ProgrammedEvent evt1;
    SimulatedSequence::SimulateAction(STICK_DOWN_RIGHT, false,
                                      evt1.event_states);
    evt1.frames = 500;
    evt1.id = "DOWN RIGHT";
    actions.push_back(evt1);

    // stick down
    ProgrammedEvent evt2;
    SimulatedSequence::SimulateAction(STICK_DOWN, false, evt2.event_states);
    evt2.frames = 100;
    evt2.id = "DOWN";
    actions.push_back(evt2);

    // stick down and fire down
    ProgrammedEvent evt3;
    SimulatedSequence::SimulateAction(STICK_DOWN, true, evt3.event_states);
    evt3.frames = 100;
    evt3.id = "DOWN FIRE_PRESS";
    actions.push_back(evt3);

    // stick down and fire up
    ProgrammedEvent evt4;
    SimulatedSequence::SimulateAction(STICK_DOWN, false, evt4.event_states);
    evt4.frames = 100;
    evt4.id = "DOWN FIRE_RELEASE";
    actions.push_back(evt4);

    // reverse the order
    std::reverse(actions.begin(), actions.end());
}

} // namespace SenselessSoccer
