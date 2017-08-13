#include "running.h"
#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Running::Running(Player &p) : PlayerState(p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Running::OnStart() {
    player.player_sprite->SetAnimation("run_east");
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Running::OnStep(const float dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Running::OnEnd() {
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Running::StateOver() {
    if (player.physical->velocity.magnitude() == 0) {
        next_state = PLAYER_STATE_STAND;
        return true;
    }
    return false;
}

} // SenselessSoccer
