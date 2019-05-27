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
 * @file intercept.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "intercept.h"
#include "../player.h"

namespace SenselessSoccer {

// -----------------------------------------------------------------------------
// Intercept
// -----------------------------------------------------------------------------
Intercept::Intercept(Player &p) : Locomotion(p) { evader = nullptr; }

// --------------------------------------------------
// Init
// --------------------------------------------------
void Intercept::Init(GameLib::Physical &_evader) { evader = &_evader; }

// -----------------------------------------------------------------------------
// OnStart
// -----------------------------------------------------------------------------
void Intercept::OnStart() {
    state_over = false;
    destination_reached = false;
}

// -----------------------------------------------------------------------------
// OnStep
// -----------------------------------------------------------------------------
void Intercept::OnStep() {

    // direction to evader
    GameLib::Vector3 to_evader = (evader->position) - (player.physical.position);

    /*  look ahead time in proportion to distance from evader, and inversely
       proportional
        to the sum of the velocities
    */
    float divider = 0;
    float look_ahead_time = 0;

    divider = player.velocity.magnitude() + evader->velocity.magnitude();

    if (divider < GameLib::TOL) {
        look_ahead_time = (to_evader.magnitude() / divider);
    }

    // seek to the predicted future position of the evader
    GameLib::Vector3 actual_target = (evader->position + evader->velocity * look_ahead_time);

    // behaviours dont take ball height into account but 3d vector math does
    // (otherwise -> flying players!)
    actual_target.z = 0;

    // this must always be called to advance the state!
    seek(actual_target);
}

// -----------------------------------------------------------------------------
// OnEnd
// -----------------------------------------------------------------------------
void Intercept::OnEnd() {
    Locomotion::OnEnd();

    destination_reached = true;
    state_over = true;
}

// -----------------------------------------------------------------------------
// StateOver
// -----------------------------------------------------------------------------
bool Intercept::StateOver() { return state_over; }

// -----------------------------------------------------------------------------
// Cancel
// -----------------------------------------------------------------------------
void Intercept::Cancel() { state_over = true; }

// --------------------------------------------------
// seek
// --------------------------------------------------
void Intercept::seek(GameLib::Vector3 _target) { player.velocity = _target - player.physical.position; }

} // namespace SenselessSoccer
