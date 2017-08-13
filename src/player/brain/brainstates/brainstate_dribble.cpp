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
    timer.Start();
    player->brain.locomotion.ActivateHead(GameLib::Vector3(1, 1));
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainDribble::OnStep(const float _dt) {

    // test
    if (!player->brain.in_pitch(_dt)) {
        GameLib::Vector3 new_direction = player->physical->velocity.rotated(180).roundAngle(45);
        player->brain.locomotion.ActivateHead(new_direction);
    } else if (timer.GetTicks() > 4000) {
        timer.Start();
        change_direction();
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainDribble::OnEnd() {
    player->physical->ResetVelocity();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainDribble::StateOver() {
    if (!player->ball_under_control()) {
        return true;
    }
    return false;
}

// ------------------------------------------------------------
// ChangeToNextState
// ------------------------------------------------------------
void BrainDribble::ChangeToNextState() {
    player->brain.ChangeState(new BrainIdle(player));
}

// ------------------------------------------------------------
// change_direction
// ------------------------------------------------------------
void BrainDribble::change_direction() {
    GameLib::Vector3 new_direction = player->physical->velocity.rotated(rand() % 2 == 1 ? 45 : -45).roundAngle(45);
    player->brain.locomotion.ActivateHead(new_direction);
}
}
