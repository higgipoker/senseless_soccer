#include "brainstate_dribble.h"
#include "brainstate_idle.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
BrainDribble::BrainDribble(Player *p) : BrainState(p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void BrainDribble::OnStart() {
    std::cout << "DRIBBLE " << player->GetName() << std::endl;
    change_direction();
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainDribble::OnStep(const float _dt) {

    // test
    if(!player->brain.in_pitch(_dt)) {
        GameLib::Vector3 new_direction = player->physical->velocity.rotated(180).roundAngle(45);
        player->brain.locomotion.ActivateHead(new_direction);

    } else if(timer.GetTicks() > 1000) {
        timer.Start();
        change_direction();
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainDribble::OnEnd() {
    BrainState::OnEnd();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainDribble::StateOver() {
    if(!player->ball_under_control()) {
        next_state = BRAIN_IDLE;
        return true;
    }

    return false;
}

// ------------------------------------------------------------
// change_direction
// ------------------------------------------------------------
void BrainDribble::change_direction() {
    GameLib::Vector3 new_direction = player->physical->velocity.rotated(rand() % 2 == 1 ? 45 : -45).roundAngle(45);
    player->brain.locomotion.ActivateHead(new_direction);
}

// ------------------------------------------------------------
// Modify
// ------------------------------------------------------------
void BrainDribble::Modify(modifier mod) {

    switch(mod) {
    case DRIBBLE_CHANGE_DIRECTION:
        change_direction();
        break;
    }
}

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void BrainDribble::Init(Compass dir) {
    timer.Start();
    player->brain.locomotion.ActivateHead(Metrics::compasstoVector(dir));
}
}
