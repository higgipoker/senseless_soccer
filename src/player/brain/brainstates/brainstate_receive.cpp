#include "brainstate_receive.h"
#include "../../../team/team.h"

namespace SenselessSoccer {

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
BrainReceive::BrainReceive(Player &p) : BrainState(p) {}

// -----------------------------------------------------------------------------
// OnStart
// -----------------------------------------------------------------------------
void BrainReceive::OnStart() {
    player.brain.statename = "RECEIVE";
    next_state = BRAIN_DRIBBLE;
    player.brain.locomotion.ActivateIntercept(player.ball->physical);
}

// -----------------------------------------------------------------------------
// OnStep
// -----------------------------------------------------------------------------
void BrainReceive::OnStep(const float _dt) {}

// -----------------------------------------------------------------------------
// OnEnd
// -----------------------------------------------------------------------------
void BrainReceive::OnEnd() {
    BrainState::OnEnd();
    player.my_team->key_players.pass_recipient = nullptr;
}

// -----------------------------------------------------------------------------
// StateOver
// -----------------------------------------------------------------------------
bool BrainReceive::StateOver() {
    if (player.ball_under_control()) {
        return true;
    } else if (player.my_team->key_players.pass_recipient != &player) {
        next_state = BRAIN_SUPPORT;
        return true;
    }

    return false;
}

// -----------------------------------------------------------------------------
// Modify
// -----------------------------------------------------------------------------
void BrainReceive::Modify(modifier mod) {

    switch (mod) { break; }
}

} // namespace SenselessSoccer
