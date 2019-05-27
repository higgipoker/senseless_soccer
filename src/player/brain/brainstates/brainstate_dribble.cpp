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
 * @file brainstate_ddribble.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "brainstate_dribble.h"

#include "../../../team/team.h"
#include "brainstate_idle.h"
#include <assert.h>

namespace SenselessSoccer {

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
BrainDribble::BrainDribble(Player &p) : BrainState(p) {}

// -----------------------------------------------------------------------------
// OnStart
// -----------------------------------------------------------------------------
void BrainDribble::OnStart() {
    player.brain.statename = "DRIBBLE";
    player.gained_possession();
    player.velocity = player.last_direction;
    change_direction();
    change_direction_ticker = 0;

    // dribble state needs a joystick simulator
    // player.AttachInput(&(player.brain.joystick));
}

// -----------------------------------------------------------------------------
// OnStep
// -----------------------------------------------------------------------------
void BrainDribble::OnStep(const float _dt) {

    // TODO: use the joystick simulator to execute ideas!

    if (!player.brain.in_pitch(_dt)) {
        // stay in pitch
        GameLib::Vector3 new_direction = player.velocity.rotated(45).roundAngle(45);
        player.brain.locomotion.ActivateHead(new_direction);

    } else if (change_direction_ticker > 200) {
        // test random change dir
        change_direction_ticker = 0;
        change_direction();
    }
}

// -----------------------------------------------------------------------------
// OnEnd
// -----------------------------------------------------------------------------
void BrainDribble::OnEnd() {
    BrainState::OnEnd();
    player.lost_possession();
    player.DetatchInput();
}

// -----------------------------------------------------------------------------
// StateOver
// -----------------------------------------------------------------------------
bool BrainDribble::StateOver() {
    if (!player.ball_under_control()) {
        next_state = BRAIN_SUPPORT;
        return true;
    } else if (pass_timer_started && pass_ticker > 10) {
        return true;
    } else if (player.distance_to_goal() < 650) {
        next_state = BRAIN_SHOOT;
        return true;
    }

    return state_over;
}

// -----------------------------------------------------------------------------
// change_direction
// -----------------------------------------------------------------------------
void BrainDribble::change_direction() {
    GameLib::Vector3 new_direction = player.velocity.rotated(rand() % 2 == 1 ? 45 : -45).roundAngle(45);
    player.brain.locomotion.Cancel();
    player.brain.locomotion.ActivateHead(new_direction);
}

// -----------------------------------------------------------------------------
// Modify
// -----------------------------------------------------------------------------
void BrainDribble::Modify(modifier mod) {

    switch (mod) {
        case DRIBBLE_CHANGE_DIRECTION:
            change_direction();
            break;
        default:
            break;
    }
}

// -----------------------------------------------------------------------------
// Init
// -----------------------------------------------------------------------------
void BrainDribble::Init(Compass dir) {
    change_direction_ticker = 0;
    player.brain.locomotion.ActivateHead(Metrics::compasstoVector(dir));
}
} // namespace SenselessSoccer
