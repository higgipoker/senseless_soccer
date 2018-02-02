#include "brainstate_shoot.h"
#include "../../../team/team.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
BrainShoot::BrainShoot(Player *p) : BrainState(p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainShoot::OnStart() {
    player->brain.statename = "SHOOT";
    next_state = BRAIN_SUPPORT;
    player->Shoot();
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainShoot::OnStep(const double _dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainShoot::OnEnd() {
    BrainState::OnEnd();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainShoot::StateOver() {
    if(!player->ball_under_control()) {
        return true;
    }

    return false;
}

// ------------------------------------------------------------
// Modify
// ------------------------------------------------------------
void BrainShoot::Modify(modifier mod) {

    switch(mod) {
        break;
    }
}

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void BrainShoot::Init(Player *receiver) {

}

}// namespace SenselessSoccer


