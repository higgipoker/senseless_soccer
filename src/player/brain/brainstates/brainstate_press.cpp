#include "brainstate_press.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// BrainPress
// ------------------------------------------------------------
BrainPress::BrainPress(Player &player) : BrainState(player) {}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainPress::OnStart() {
    player.brain.statename = "PRESS";
    player.brain.locomotion.ActivateIntercept(player.ball->physical);
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainPress::OnStep(const float _dt) {}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainPress::OnEnd() { BrainState::OnEnd(); }

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainPress::StateOver() {

    // TODO: end condition: got ball, or decision to stop pressing, or decision to slide
    // etc

    if (player.ball_under_control()) {
        next_state = BRAIN_DRIBBLE;
        return true;
    }
    return false;
}

} // namespace SenselessSoccer
