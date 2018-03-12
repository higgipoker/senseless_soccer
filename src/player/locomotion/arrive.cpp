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
 * @file arrive.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "arrive.h"

#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Arrive
// ------------------------------------------------------------
Arrive::Arrive(Player &p) : Locomotion(p) {}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Arrive::OnStart() {
    state_over = false;
    destination_reached = false;
    player.velocity = destination - player.physical.position;
    last_distance = player.physical.position - destination;
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Arrive::OnStep(const float dt) {
    GameLib::Vector3 new_distance = destination - player.physical.position;

    if (new_distance.magnitude() <= 10) {
        // reached destination?
        state_over = true;
        destination_reached = true;
        player.physical.ResetVelocity();

    } else {
        // adjust for misses due to 45 degree precision
        if (new_distance.magnitude() <= last_distance.magnitude()) {
            player.velocity = destination - player.physical.position;
        }
    }

    last_distance = player.physical.position - destination;
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Arrive::OnEnd() {
    Locomotion::OnEnd();

    destination = player.physical.position;
    destination_reached = true;
    state_over = true;
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Arrive::StateOver() { return state_over; }

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void Arrive::Init(GameLib::Vector3 target) { destination = target; }

// ------------------------------------------------------------
// Cancel
// ------------------------------------------------------------
void Arrive::Cancel() { state_over = true; }

} // namespace SenselessSoccer
