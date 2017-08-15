#include "pursue.h"

#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Pursue
// ------------------------------------------------------------
Pursue::Pursue(Player *p) : Locomotion(p) {
}

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
    if(destination_reached)
        return;

    player->physical->velocity = target->position - player->physical->position;
    last_distance = target->position - player->physical->position;
    GameLib::Vector3 new_distance = target->position - player->physical->position;

    if(new_distance.magnitude() < 100) {
        destination_reached = true;
        player->physical->ResetVelocity();

    } else {
        if(new_distance.magnitude() > last_distance.magnitude()) {
            player->physical->velocity = target->position - player->physical->position;
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
bool Pursue::StateOver() {
    return state_over;
}

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void Pursue::Init(GameLib::Physical *t) {
    target = t;
}

// ------------------------------------------------------------
// Cancel
// ------------------------------------------------------------
void Pursue::Cancel(){
    state_over = true;
}

} // namespace SenselessSoccer
