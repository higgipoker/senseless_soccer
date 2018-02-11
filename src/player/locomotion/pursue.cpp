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
 * @file pursue.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "pursue.h"
#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Pursue
// ------------------------------------------------------------
Pursue::Pursue(Player *p) : Locomotion(p) { target = nullptr; }

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Pursue::OnStart() {
    state_over = false;
    destination_reached = false;
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Pursue::OnStep(const float dt) {

    player->velocity = target->position - player->physical->position;
    last_distance = target->position - player->physical->position;
    GameLib::Vector3 new_distance = target->position - player->physical->position;

    if (new_distance.magnitude() < 1) {
        player->physical->ResetVelocity();

    } else {
        if (new_distance.magnitude() > last_distance.magnitude()) {
            player->velocity = target->position - player->physical->position;
        }
    }

    last_distance = target->position - player->physical->position;
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Pursue::OnEnd() {
    Locomotion::OnEnd();

    destination_reached = true;
    state_over = true;
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Pursue::StateOver() { return state_over; }

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void Pursue::Init(GameLib::Physical *t) { target = t; }

// ------------------------------------------------------------
// Cancel
// ------------------------------------------------------------
void Pursue::Cancel() { state_over = true; }

} // namespace SenselessSoccer
