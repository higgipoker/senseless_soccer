#include "player_state.h"

#include "../player.h"

#include "running.h"
#include "standing.h"
#include "sliding.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
PlayerState::PlayerState(Player &p) : player(p), next_state(PLAYER_STATE_NONE) {
}

// ------------------------------------------------------------
// ChangeToNextState
// ------------------------------------------------------------
void PlayerState::ChangeToNextState() {

    switch(next_state) {

    case PLAYER_STATE_STAND:
        player.ChangeState(new Standing(player));
        break;

    case PLAYER_STATE_RUN:
        player.ChangeState(new Running(player));
        break;

    case PLAYER_STATE_SLIDE:
        player.ChangeState(new Sliding(player));
        break;

    case PLAYER_STATE_NONE:
    default:
        break;
    }
}

// ------------------------------------------------------------
// handle_input
// ------------------------------------------------------------
void PlayerState::handle_input() {

    // fresh start
    player.physical->ResetVelocity();

    // poll for inputs
    player.input->Update();

    // up
    if(player.input->event_states[GameLib::UP]) {
        player.physical->velocity.y = -1;
    }

    // down
    if(player.input->event_states[GameLib::DOWN]) {
        player.physical->velocity.y = 1;
    }

    // left
    if(player.input->event_states[GameLib::LEFT]) {
        player.physical->velocity.x = -1;
    }

    // right
    if(player.input->event_states[GameLib::RIGHT]) {
        player.physical->velocity.x = 1;
    }
}

// ------------------------------------------------------------
// HandleEvent
// ------------------------------------------------------------
bool PlayerState::HandleEvent(ControllerEvent event) {
    switch(event.id) {

    case FIRE_RELEASE:
        if(player.ball_under_control()) {
            player.kick(event.param);
            return true;
        }

        break;

    case FIRE_TAP:
        break;

    case FIRE_DOUBLE_TAP:
        break;

    case FIRE_PRESS:
        break;

    case NO_EVENT:
    default:
        break;
    }

    return false;
}
} // SenselessSoccer
