#include "standing.h"
#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Standing::Standing (Player &p)
    : PlayerState (p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Standing::OnStart() {
    player.player_sprite->SetAnimation ("stand_south");
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Standing::OnStep (const float dt) {
    GameLib::Vector3 to_ball = player.ball->physical->position - player.physical->position;
    player.player_sprite->SetStandingAnimation (to_ball.roundAngle (45));
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Standing::OnEnd() {
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Standing::StateOver() {
    if (player.velocity.magnitude()) {
        next_state = PLAYER_STATE_RUN;
        return true;
    }

    return false;
}

} // SenselessSoccer
