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
 * @file brainstate_support.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "brainstate_support.h"

#include "../../../team/team.h"
#include "../../player.h"
#include <gamelib/utils/log.h>

namespace SenselessSoccer {

// ------------------------------------------------------------
// Support
// ------------------------------------------------------------
BrainSupport::BrainSupport(Player &p) : BrainState(p) {
    last_ball_sector = last_target_sector = -1;
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainSupport::OnStart() { player.brain.statename = "SUPPORT"; }

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainSupport::OnStep(const float dt) {

    GameLib::Vector3 destination;

    // get the current ball sector
    unsigned int ball_sector =
        player.pitch->grid.PointToSector(player.ball->GetPosition());

    // make sure the ball is in the pitch
    if (ball_sector >= player.pitch->grid.NumberSectors())
        return;

    // save for next time round
    last_ball_sector = ball_sector;

    // get the new target sector depending on player role
    unsigned int target_sector =
        player.role->GetPosition(ball_sector, player.my_team->side);

    // modify based on tactical instructions?
    if (modifiers.size()) {
        switch (modifiers[0]) {

            //
            // stay a couple of sectors back
            //
            case SUPPORT_BACKUP:
                target_sector = mod_for_backup(target_sector);
                break;

            //
            // run towards the ball
            //
            case SUPPORT_PASS:
                mod_for_pass();
                break;

            //
            // bomb forward
            //
            case SUPPORT_RUN:
                player.brain.locomotion.ActivateHead(Metrics::compasstoVector(NORTH));
                break;

            case MODIFIER_NONE:
            default:
                break;
        }
    }

    // only if the target sector has changed
    if (target_sector != last_target_sector) {
        destination = player.pitch->grid.GetSectorCenter(target_sector).vector();
        player.brain.locomotion.ActivateArrive(destination);
    }

    last_target_sector = target_sector;

    // check stop condition
    GameLib::Vector3 distance = player.physical.position - destination;

    if (distance.magnitude() < 10) {
        player.brain.locomotion.Cancel();
        return;
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainSupport::OnEnd() { BrainState::OnEnd(); }

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainSupport::StateOver() {
    if (BrainState::StateOver()) {
        return true;
    } else if (player.ball_under_control()) {
        next_state = BRAIN_DRIBBLE;
        return true;
    }
    //     else if(player.my_team->key_players.player_in_possession == nullptr){
    //         next_state = BRAIN_GETBALL;
    //         return true;
    //     }

    return false;
}

// ------------------------------------------------------------
// Modify
// ------------------------------------------------------------
void BrainSupport::Modify(modifier mod) {
    modifiers.clear();

    if (mod != MODIFIER_NONE) {
        modifiers.push_back(mod);
    }

    last_ball_sector = 999;
    last_target_sector = 999;
}

// ------------------------------------------------------------
// mod_for_backup
// ------------------------------------------------------------
unsigned int BrainSupport::mod_for_backup(unsigned int sector) {
    return player.pitch->grid.OffsetSectorY(sector, 2);
}

// ------------------------------------------------------------
// mod_for_pass
// ------------------------------------------------------------
void BrainSupport::mod_for_pass() {

    // for now, just run towards ball
    player.brain.locomotion.ActivatePursue(player.ball->physical);
}

} // namespace SenselessSoccer
