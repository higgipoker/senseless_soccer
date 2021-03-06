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
 * @file running.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "running.h"

#include "../player.h"
#include <gamelib/physics/collision_detector.h>

namespace SenselessSoccer {

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
Running::Running(Player &p) : PlayerState(p) {}

// -----------------------------------------------------------------------------
// OnStart
// -----------------------------------------------------------------------------
void Running::OnStart() {}

// -----------------------------------------------------------------------------
// OnStep
// -----------------------------------------------------------------------------
void Running::OnStep(const float dt) {
    // set the animation based on velocity (running direction)
    player.player_sprite->SetRunningAnimation(player.velocity.roundAngle(45));

    // check for collision with ball (dribble)
    if (GameLib::CollisionDetector::collision(player.dribble_circle, player.ball->GetCollidable())) {
        player.do_dribble(player.velocity.normalised());
    }
}

// -----------------------------------------------------------------------------
// OnEnd
// -----------------------------------------------------------------------------
void Running::OnEnd() {}

// -----------------------------------------------------------------------------
// StateOver
// -----------------------------------------------------------------------------
bool Running::StateOver() {
    if (player.velocity.magnitude() < GameLib::TOL) {
        next_state = PLAYER_STATE_STAND;
        return true;

    } else if (player.sliding == true) {
        next_state = PLAYER_STATE_SLIDE;
        return true;
    }

    return false;
}

// -----------------------------------------------------------------------------
// HandleEvent
// -----------------------------------------------------------------------------
bool Running::HandleEvent(ControllerEvent event) {

    if (!PlayerState::HandleEvent(event)) {

        switch (event.id) {

            case FIRE:
                if (event.status == PRESSED) {
                    if (!player.sliding) {
                        if (!player.ball_under_control()) {
                            player.slide_tackle();
                            return true;
                        }
                    }
                }
                break;

            case DPAD_LEFT:
                break;

            case DPAD_RIGHT:
                break;

            case DPAD_UP:
                break;

            case DPAD_DOWN:
                break;

            case NO_EVENT:
                break;
        }
    }

    return false;
}

} // SenselessSoccer
