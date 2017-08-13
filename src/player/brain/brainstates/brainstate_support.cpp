#include "brainstate_support.h"

#include "../../player.h"
#include <gamelib/utils/log.h>

namespace SenselessSoccer {

// ------------------------------------------------------------
// Support
// ------------------------------------------------------------
BrainSupport::BrainSupport(Player *p) : BrainState(p) {
    last_ball_sector = last_target_sector = -1;
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainSupport::OnStart() {
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainSupport::OnStep(const float dt) {

    GameLib::Vector3 destination;

    // get the current ball sector
    int ball_sector = player->pitch->grid.PointToSector(player->ball->GetPosition());

    // if ball sector is valid and has changed
    if (ball_sector >= 0 && ball_sector != last_ball_sector) {

        // get the new target sector depending on player role
        int target_sector = player->role->GetPosition(ball_sector);

        // modify based on tactical instructions?
        if (modifiers.size()) {
            switch (modifiers[0]) {

            case SUPPORT_BACKUP:
                target_sector = mod_for_backup(target_sector);
                break;

            case SUPPORT_PASS:
                player->brain.locomotion.ActivatePursue(player->ball->physical);
                break;

            case SUPPORT_RUN:
                break;

            case MODIFIER_NONE:
            default:
                break;
            }
        } else {
            // only if the target sector has changed
            if (target_sector != last_target_sector) {
                last_target_sector = target_sector;
                destination = player->pitch->grid.GetSectorCenter(target_sector).vector();
                player->brain.locomotion.ActivateArrive(destination);
            }
        }

        // save for next time round
        last_ball_sector = ball_sector;
    }

    // check stop condition
    GameLib::Vector3 distance = player->physical->position - destination;
    if (distance.magnitude() < 10) {
        player->physical->ResetVelocity();
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainSupport::OnEnd() {
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainSupport::StateOver() {
}

// ------------------------------------------------------------
// Modify
// ------------------------------------------------------------
void BrainSupport::Modify(modifier mod) {
    modifiers.clear();
    modifiers.push_back(mod);
    last_ball_sector = -1;
}

// ------------------------------------------------------------
// mod_for_backup
// ------------------------------------------------------------
int BrainSupport::mod_for_backup(int sector) {
    return player->pitch->grid.OffsetSectorY(sector, 2);
}

// ------------------------------------------------------------
// mod_for_pass
// ------------------------------------------------------------
void BrainSupport::mod_for_pass() {

    // for now, just run towards ball
}

} // namespace SenselessSoccer
