#include "brainstate_cover.h"

#include "../../player.h"
#include "../../../team/team.h"
#include <gamelib/utils/log.h>

namespace SenselessSoccer {

// ------------------------------------------------------------
// BrainCover
// ------------------------------------------------------------
BrainCover::BrainCover (Player *p) : BrainState (p) {
    last_ball_sector = last_target_sector = -1;
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainCover::OnStart() {
    player->brain.statename = "COVER";
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainCover::OnStep (const float dt) {
    GameLib::Vector3 destination;

    // get the current ball sector
    int ball_sector = player->pitch->grid.PointToSector (player->ball->GetPosition());

    // if ball sector is valid and has changed
    if (ball_sector >= 0 && ball_sector != last_ball_sector) {

        // get the new target sector depending on player role
        int target_sector = player->role->GetPosition (ball_sector, player->my_team->side);

        // modify based on tactical instructions?
        int m = 0;

        if (modifiers.size()) {
            switch (modifiers[0]) {

                case COVER_PRESS:
                    m = -1;
                    break;

                case COVER_PRESS_HIGH:
                    m = -2;
                    break;

                case COVER_SHADOW:
                    m = 1;
                    break;

                case COVER_SHADOW_DEEP:
                    m = 2;
                    break;

                case MODIFIER_NONE:
                default:
                    break;
            }
        }

        target_sector = player->pitch->grid.OffsetSectorY (target_sector, m);

        // only if the target sector has changed
        if (target_sector != last_target_sector) {
            last_target_sector = target_sector;
            destination = player->pitch->grid.GetSectorCenter (target_sector).vector();
            player->brain.locomotion.ActivateArrive (destination);
        }

        // save for next time round
        last_ball_sector = ball_sector;
    }

    // check stop condition
    GameLib::Vector3 distance = player->physical->position - destination;

    if (distance.magnitude() < 10) {
        player->brain.locomotion.Cancel();
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainCover::OnEnd() {
    BrainState::OnEnd();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainCover::StateOver() {
}

// ------------------------------------------------------------
// Modify
// ------------------------------------------------------------
void BrainCover::Modify (modifier mod) {
    modifiers.clear();
    modifiers.push_back (mod);
    last_ball_sector = -1;
}

} // namespace SenselessSoccer
