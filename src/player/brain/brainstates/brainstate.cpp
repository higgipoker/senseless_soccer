#include "brainstate.h"
#include "brainstate_cover.h"
#include "brainstate_dribble.h"
#include "brainstate_getball.h"
#include "brainstate_idle.h"
#include "brainstate_support.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// BrainState
// ------------------------------------------------------------
BrainState::BrainState(Player *p) {
    player = p;
    next_state = BRAIN_NONE;
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainState::OnStart() {
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainState::OnStep(const float _dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainState::OnEnd() {
    player->brain.locomotion.Cancel();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainState::StateOver() {
    return false;
}

// ------------------------------------------------------------
// ChangeToNextState
// ------------------------------------------------------------
void BrainState::ChangeToNextState() {

    switch(next_state) {
    case BRAIN_COVER:
        player->brain.ChangeState(new BrainCover(player));
        break;

    case BRAIN_DRIBBLE:
        player->brain.ChangeState(new BrainDribble(player));
        break;

    case BRAIN_GETBALL:
        break;

    case BRAIN_IDLE:
        break;

    case BRAIN_SUPPORT:
        break;


    case BRAIN_NONE:
    default:
        break;
    }

}

// ------------------------------------------------------------
// Modify
// ------------------------------------------------------------
void BrainState::Modify(modifier mod) {
}
}
