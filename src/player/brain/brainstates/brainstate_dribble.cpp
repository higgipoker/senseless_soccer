#include "brainstate_dribble.h"

#include <assert.h>
#include "brainstate_idle.h"
#include "../../../team/team.h"

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
    player->brain.statename = "DRIBBLE";
    player->OnGainedPossession();
    player->physical->velocity = player->last_direction;
    assert(player->physical->velocity.magnitude());
    change_direction();
    timer.Start();
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void BrainDribble::OnStep(const float _dt) {

    std::cout << player->distance_to_goal() << std::endl;
    if(!player->brain.in_pitch(_dt)) {
        /*********************************************
        * stay in pitch
        * *******************************************/
        GameLib::Vector3 new_direction = player->physical->velocity.rotated(45).roundAngle(45);
        player->brain.locomotion.ActivateHead(new_direction);

    } else if(timer.GetTicks() > 2000) {
        /*********************************************
        * test random change dir
        * *******************************************/
        timer.Start();
        change_direction();
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void BrainDribble::OnEnd() {
    BrainState::OnEnd();
    player->OnLostPossession();
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool BrainDribble::StateOver() {
    if(!player->ball_under_control()) {
        next_state = BRAIN_SUPPORT;
        return true;
    }

    else if(!pass_timer_started && player->my_team->key_players.short_pass_candidates.size()){
        pass_timer_started = true;
        pass_timer.Start();
        next_state = BRAIN_PASS;
    }

    else if(pass_timer_started && pass_timer.GetTicks()>100){
        return true;
    }

    else if(player->distance_to_goal() < 650){
        next_state = BRAIN_SHOOT;
        return true;
    }

    return state_over;
}

// ------------------------------------------------------------
// change_direction
// ------------------------------------------------------------
void BrainDribble::change_direction() {
    GameLib::Vector3 new_direction = player->physical->velocity.rotated(rand() % 2 == 1 ? 45 : -45).roundAngle(45);
    player->brain.locomotion.Cancel();
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
