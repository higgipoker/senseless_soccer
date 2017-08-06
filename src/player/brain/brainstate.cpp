#include "brainstate.h"

namespace SenselessSoccer {

BrainState::BrainState(Player *p) {
    player = p;
}

void BrainState::OnStart() {
}
void BrainState::OnStep(const float _dt) {
}
void BrainState::OnEnd() {
}
bool BrainState::StateOver() {
    return false;
}
void BrainState::ChangeToNextState() {
}
}
