#include "brainstate.h"
#include "brainstate_cover.h"
#include "brainstate_dribble.h"
#include "brainstate_getball.h"
#include "brainstate_idle.h"
#include "brainstate_support.h"
#include "brainstate_pass.h"
#include "brainstate_receive.h"
#include "brainstate_shoot.h"
#include "brainstate_clear.h"
#include "brainstate_press.h"
#include "../../../team/team.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// BrainState
// ------------------------------------------------------------
BrainState::BrainState (Player *p) {
    player = p;
    next_state = BRAIN_NONE;
    state_over = false;
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainState::OnStart() {
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainState::OnStep (const float _dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainState:: OnEnd() {
    player->brain.locomotion.Cancel();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainState::StateOver() {
    if (player->my_team->key_players.pass_recipient == player) {
        next_state = BRAIN_RECEIVE;
        return true;
    }

    return false;
}

// ------------------------------------------------------------
// ChangeToNextState
// ------------------------------------------------------------
void BrainState::ChangeToNextState() {

    switch (next_state) {
        case BRAIN_COVER:
            player->brain.ChangeState (new BrainCover (player));
            break;

        case BRAIN_DRIBBLE:
            player->brain.ChangeState (new BrainDribble (player));
            break;

        case BRAIN_GETBALL:
            player->brain.ChangeState (new BrainGetBall (player));
            break;

        case BRAIN_IDLE:
            player->brain.ChangeState (new BrainIdle (player));
            break;

        case BRAIN_SUPPORT:
            player->brain.ChangeState (new BrainSupport (player));
            break;

        case BRAIN_PASS:
            player->brain.ChangeState (new BrainPass (player));
            break;

        case BRAIN_RECEIVE:
            player->brain.ChangeState (new BrainReceive (player));
            break;

        case BRAIN_SHOOT:
            player->brain.ChangeState (new BrainShoot (player));
            break;

        case BRAIN_PRESS:
            player->brain.ChangeState (new BrainPress (player));
            break;

        case BRAIN_CLEAR:
            player->brain.ChangeState (new BrainClear (player));
            break;

        case BRAIN_NONE:
        default:
            break;
    }

}

// ------------------------------------------------------------
// Modify
// ------------------------------------------------------------
void BrainState::Modify (modifier mod) {
}
}
