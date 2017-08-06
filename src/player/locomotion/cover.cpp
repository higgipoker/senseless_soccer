#include "cover.h"

#include "../player.h"
#include <gamelib/utils/log.h>

namespace SenselessSoccer {

Cover::Cover(Player *p) : Locomotion(p) {
    last_ball_sector = last_target_sector = -1;
}

void Cover::OnStart() {
    state_over = false;
    destination_reached = false;
    modifier = NONE;
}

void Cover::OnStep(const float dt) {

    // get the current ball sector
    int ball_sector = player->pitch->grid.PointToSector(player->ball->GetPosition());

    // if ball sector is valid and has changed
    if (ball_sector >= 0 && ball_sector != last_ball_sector) {

        // get the new target sector depending on player role
        int target_sector = player->role->GetPosition(ball_sector);

        // modify based on tactical instructions?
        switch (modifier) {

        case COVER_PRESS:
            target_sector = player->pitch->grid.OffsetSectorY(target_sector, -2);
            break;

        case COVER_SHADOW:
            target_sector = player->pitch->grid.OffsetSectorY(target_sector, 2);
            break;

        case NONE:
        default:
            break;
        }

        // only if the target sector has changed
        if (target_sector != last_target_sector) {
            last_target_sector = target_sector;
            destination = player->pitch->grid.GetSectorCenter(target_sector).vector();
            player->physical->velocity = destination - player->physical->position;
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

void Cover::OnEnd() {
    destination = player->physical->position;
    destination_reached = true;
    state_over = true;
}

bool Cover::StateOver() {
    return state_over;
}

void Cover::ChangeToNextState() {
}

void Cover::Modify(Modifier mod) {
    modifier = mod;
}

} // namespace SenselessSoccer
