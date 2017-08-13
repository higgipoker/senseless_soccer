#include "brainstate_idle.h"
#include "brainstate_dribble.h"

namespace SenselessSoccer {
BrainIdle::BrainIdle(Player *player) : BrainState(player) {
}
void BrainIdle::OnStart() {
}

void BrainIdle::OnStep(const float _dt) {
}

void BrainIdle::OnEnd() {
}

bool BrainIdle::StateOver() {
    if (player->ball_under_control()) {
        return true;
    }
    return false;
}

void BrainIdle::ChangeToNextState() {
    player->brain.ChangeState(new BrainDribble(player));
}
}
