#include "cover.h"

#include "../player.h"
#include <gamelib/utils/log.h>

namespace SenselessSoccer {

Cover::Cover(Player *p) : Locomotion(p) { last_ball_sector = -1; }

void Cover::OnStart() {
    state_over = false;
    destination_reached = false;
}

void Cover::OnStep(const float dt) {
    int ball_sector = player->pitch->grid.CoordinatesToSector(player->ball->physical->position.x, player->ball->physical->position.y);

    if (ball_sector != last_ball_sector) {
        int target_sector = player->role->GetPosition(ball_sector);

        // modify?
        switch (modifier) {
        case COVER_PRESS:
            break;
        case COVER_SHADOW:
            break;

        default:
            break;
        }

        if (target_sector != last_target_sector) {
            last_target_sector = target_sector;
            destination = player->pitch->grid.GetSectorCenter(target_sector).vector();
            player->physical->velocity = destination - player->physical->position;
        }
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

bool Cover::StateOver() { return state_over; }

void Cover::ChangeToNextState() {}

void Cover::Modify(Modifier mod) { modifier = mod; }

} // namespace SenselessSoccer
