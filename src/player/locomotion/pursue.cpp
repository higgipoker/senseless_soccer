#include "pursue.h"

#include "../player.h"

namespace SenselessSoccer {

Pursue::Pursue(Player *p) : Locomotion(p) {}

void Pursue::OnStart() {
    state_over = false;
    destination_reached = false;
}

void Pursue::OnStep(const float dt) {
    if (destination_reached)
        return;

    player->physical->velocity = target->position - player->physical->position;
    last_distance = target->position - player->physical->position;
    GameLib::Vector3 new_distance = target->position - player->physical->position;

    if (player->physical->position.equals(destination, 5)) {
        destination_reached = true;
        player->physical->ResetVelocity();

    } else {
        if (new_distance.magnitude() > last_distance.magnitude()) {
            player->physical->velocity = target->position - player->physical->position;
        }
    }

    last_distance = target->position - player->physical->position;
}

void Pursue::OnEnd() {
    destination_reached = true;
    state_over = true;
}

bool Pursue::StateOver() { return state_over; }

void Pursue::ChangeToNextState() {}

void Pursue::Init(GameLib::Physical *t) { target = t; }

void Pursue::Modify(Modifier mod) {}

} // namespace SenselessSoccer
