#include "brainstate_pass.h"
#include "../../../team/team.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
BrainPass::BrainPass(Player &p) : BrainState(p) {}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainPass::OnStart() {
    player.brain.statename = "PASS";
    next_state = BRAIN_SUPPORT;
    player.my_team->key_players.pass_recipient =
        player.my_team->key_players.short_pass_candidates[0];
    player.short_pass();
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainPass::OnStep(const float _dt) {}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainPass::OnEnd() { BrainState::OnEnd(); }

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainPass::StateOver() {
    if (!player.ball_under_control()) {
        return true;
    }

    return false;
}

// ------------------------------------------------------------
// Modify
// ------------------------------------------------------------
void BrainPass::Modify(modifier mod) {

    switch (mod) { break; }
}

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void BrainPass::Init(Player *receiver) {}

} // namespace SenselessSoccer
