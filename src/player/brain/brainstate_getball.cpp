#include "brainstate_getball.h"

namespace SenselessSoccer {
BrainGetBall::BrainGetBall(Player *player) : BrainState(player) {
}
void BrainGetBall::OnStart() {
}

void BrainGetBall::OnStep(const float _dt) {
}

void BrainGetBall::OnEnd() {
}

bool BrainGetBall::StateOver() {
    return false;
}

void BrainGetBall::ChangeToNextState() {
}
}
