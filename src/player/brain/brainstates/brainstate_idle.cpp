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
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainIdle::OnStep(const float _dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainIdle::OnEnd() {
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainIdle::StateOver() {
    if (player->ball_under_control()) {
        return true;
    }
    return false;
}

// ------------------------------------------------------------
// ChangeToNextState
// ------------------------------------------------------------
void BrainIdle::ChangeToNextState() {
    player->brain.ChangeState(new BrainDribble(player));
}
}
