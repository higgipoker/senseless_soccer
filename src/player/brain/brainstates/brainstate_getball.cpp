#include "brainstate_getball.h"

namespace SenselessSoccer {

// -----------------------------------------------------------------------------
// BrainGetBall
// -----------------------------------------------------------------------------
BrainGetBall::BrainGetBall(Player &player) : BrainState(player) {}

// -----------------------------------------------------------------------------
// OnStart
// -----------------------------------------------------------------------------
void BrainGetBall::OnStart() {
    player.brain.statename = "GET BALL";
    player.brain.locomotion.ActivatePursue(player.ball->physical);
}

// -----------------------------------------------------------------------------
// OnStep
// -----------------------------------------------------------------------------
void BrainGetBall::OnStep(const float _dt) {}

// -----------------------------------------------------------------------------
// OnEnd
// -----------------------------------------------------------------------------
void BrainGetBall::OnEnd() { BrainState::OnEnd(); }

// -----------------------------------------------------------------------------
// StateOver
// -----------------------------------------------------------------------------
bool BrainGetBall::StateOver() {
    if (player.ball_under_control()) {
        next_state = BRAIN_DRIBBLE;
        return true;
    }
    return false;
}
}
