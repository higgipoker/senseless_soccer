#include "sliding.h"
#include "../player.h"
#include <gamelib/physics/collision_detector.h>

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
    player.running_speed = player.DEFAULT_SPEED * 2;
    dir = player.last_direction;
    start = player.physical->position;

    // set the animation based on velocity (running direction)
    player.player_sprite->SetSlidingAnimation(player.velocity.roundAngle(45));
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Sliding::OnStep(const float dt) {
    if (player.running_speed > 100) {
        player.running_speed -= 100;
    }

    player.velocity = dir;

    // check for collision with ball (dribble)
    if (GameLib::CollisionDetector::collision(player.dribble_circle, player.ball->GetCollidable())) {
        player.do_slide_tackle(player.velocity.normalised());
    }
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Sliding::OnEnd() {
    player.sliding = false;
    player.running_speed = player.DEFAULT_SPEED;
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Sliding::StateOver() {

    if (getting_up && ++down_frames > 100) {
        next_state = PLAYER_STATE_RUN;
        getting_up = false;
        return true;
    }

    GameLib::Vector3 dist = player.physical->position - start;

    if (!getting_up && dist.magnitude() > 60) {
        getting_up = true;
        dir.reset();
        down_frames = 0;
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
