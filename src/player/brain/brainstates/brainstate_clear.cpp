#include "brainstate_clear.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// BrainClear
// ------------------------------------------------------------
BrainClear::BrainClear(Player *player) : BrainState(player) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainClear::OnStart() {
    BrainState::OnStart();
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainClear::OnStep(const float _dt) {
    BrainState::OnStep(_dt);
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainClear::OnEnd() {
    BrainState::OnEnd();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainClear::StateOver() {
    return false;
}

}// namespace SenselessSoccer
