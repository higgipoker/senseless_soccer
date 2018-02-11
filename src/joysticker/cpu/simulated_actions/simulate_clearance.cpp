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
 * @file simulate_clearance.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "simulate_clearance.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// SimulatedClearance
// ------------------------------------------------------------
SimulatedClearance::SimulatedClearance() {

    // an event to reuse
    ProgrammedEvent evt;

    // press and hold fire
    for (unsigned int i = 0; i < 10; ++i) {
        evt.event_states[GameLib::FIRE_DOWN] = true;
        evt.frames = 5;
        actions.push_back(evt);
    }

    // start pulling back (down) for height
    for (unsigned int i = 0; i < 50; ++i) {
        evt.event_states[GameLib::FIRE_DOWN] = true;
        evt.event_states[GameLib::DOWN] = true;
        evt.frames = 5;
        actions.push_back(evt);
    }
}

} // namespace SenselessSoccer
