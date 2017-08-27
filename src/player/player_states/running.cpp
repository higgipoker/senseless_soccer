#include "running.h"

#include <gamelib/physics/collision_detector.h>
#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Running::Running(Player &p) : PlayerState(p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Running::OnStart() {
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Running::OnStep(const float dt) {
    // set the animation based on velocity (running direction)
    player.player_sprite->SetRunningAnimation(player.physical->velocity.roundAngle(45) );

    // check for collision with ball (dribble)
    if(GameLib::CollisionDetector::collision(player.dribble_circle, player.ball->GetCollidable())) {
        player.do_dribble(player.physical->velocity.normalised());
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Running::OnEnd() {
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Running::StateOver() {
    if(player.physical->velocity.magnitude() == 0) {
        next_state = PLAYER_STATE_STAND;
        return true;
    }else if(player.sliding == true) {
        next_state = PLAYER_STATE_SLIDE;
        return true;
    }

    return false;
}

} // SenselessSoccer
