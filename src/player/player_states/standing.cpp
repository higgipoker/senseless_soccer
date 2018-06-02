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
 * @file standing.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "standing.h"
#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Standing::Standing(Player &p) : PlayerState(p) {}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Standing::OnStart() { player.player_sprite->SetAnimation("stand_south"); }

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Standing::OnStep(const float dt) {
    GameLib::Vector3 to_ball = player.ball->physical.position - player.physical.position;
    player.player_sprite->SetStandingAnimation(to_ball.roundAngle(45));
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Standing::OnEnd() {}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Standing::StateOver() {
    if (player.velocity.magnitude() > GameLib::TOL) {
        next_state = PLAYER_STATE_RUN;
        return true;
    }

    return false;
}

} // SenselessSoccer
