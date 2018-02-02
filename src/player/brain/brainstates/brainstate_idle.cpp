#include "brainstate_idle.h"
#include "brainstate_dribble.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// BrainIdle
// ------------------------------------------------------------
BrainIdle::BrainIdle(Player *player) : BrainState(player) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainIdle::OnStart() {
    player->brain.statename = "IDLE";
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainIdle::OnStep(const double _dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainIdle::OnEnd() {
    BrainState::OnEnd();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainIdle::StateOver() {
    if(player->ball_under_control()) {
        next_state = BRAIN_DRIBBLE;
        return true;
    }

    return false;
}

}
