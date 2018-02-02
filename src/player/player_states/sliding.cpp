#include "sliding.h"
#include <gamelib/physics/collision_detector.h>
#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Sliding::Sliding(Player &p) : PlayerState(p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Sliding::OnStart() {
    player.running_speed = 7000;
    dir = player.last_direction;
    start = player.physical->position;

    // set the animation based on velocity (running direction)
    player.player_sprite->SetSlidingAnimation(player.velocity.roundAngle(45));
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Sliding::OnStep(const double dt) {
    if(player.running_speed > 100) {
        player.running_speed -= 100;
    }

    player.velocity = dir;

    // check for collision with ball (dribble)
    if(GameLib::CollisionDetector::collision(player.dribble_circle, player.ball->GetCollidable())) {
        player.do_slide_tackle(player.velocity.normalised());
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Sliding::OnEnd() {
    player.sliding = false;
    player.running_speed = 3000;
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Sliding::StateOver() {

    if(getting_up && timer.GetTicks() > 600) {
        next_state = PLAYER_STATE_RUN;
        getting_up = false;
        return true;
    }

    GameLib::Vector3 dist = player.physical->position - start;

    if(!getting_up && dist.magnitude() > 60) {
        getting_up = true;
        dir.reset();
        timer.Start();
        return false;
    }

    return false;
}

// ------------------------------------------------------------
// handle_input
// ------------------------------------------------------------
void Sliding::handle_input() {

}

} // SenselessSoccer

