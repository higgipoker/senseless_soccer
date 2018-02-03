#include "arrive.h"

#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Arrive
// ------------------------------------------------------------
Arrive::Arrive (Player *p) : Locomotion (p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Arrive::OnStart() {
    state_over = false;
    destination_reached = false;
    player->velocity = destination - player->physical->position;
    last_distance = player->physical->position - destination;
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Arrive::OnStep (const float dt) {
    GameLib::Vector3 new_distance = destination - player->physical->position;

    if (new_distance.magnitude() <= 10) {
        // reached destination?
        state_over = true;
        destination_reached = true;
        player->physical->ResetVelocity();

    } else {
        // adjust for misses due to 45 degree precision
        if (new_distance.magnitude() <= last_distance.magnitude()) {
            player->velocity = destination - player->physical->position;
        }
    }

    last_distance = player->physical->position - destination;
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Arrive::OnEnd() {
    Locomotion::OnEnd();

    destination = player->physical->position;
    destination_reached = true;
    state_over = true;
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Arrive::StateOver() {
    return state_over;
}

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void Arrive::Init (GameLib::Vector3 target) {
    destination = target;
}

// ------------------------------------------------------------
// Cancel
// ------------------------------------------------------------
void Arrive::Cancel() {
    state_over = true;
}

} // namespace SenselessSoccer
