#include "player_state.h"

#include "../player.h"

#include "running.h"
#include "standing.h"

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

    case PLAYER_STATE_NONE:
    default:
        break;
    }
}

} // SenselessSoccer
