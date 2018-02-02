#include "intercept.h"

#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Intercept
// ------------------------------------------------------------
Intercept::Intercept(Player *p) : Locomotion(p) {
    evader = nullptr;
}

// --------------------------------------------------
// Init
// --------------------------------------------------
void Intercept::Init(GameLib::Physical *_evader) {
    evader = _evader;
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Intercept::OnStart() {
    state_over = false;
    destination_reached = false;
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Intercept::OnStep(const double dt) {

    // direction to evader
    GameLib::Vector3 to_evader = (evader->position) - (player->physical->position);

    // this will be set depending on the following 2 possibilities
    GameLib::Vector3 actual_target;

    /* 	look ahead time in proportion to distance from evader, and inversely proportional
    	to the sum of the velocities
    */
    double divider = 0;
    double look_ahead_time = 0;

    divider =  player->velocity.magnitude() + evader->velocity.magnitude();

    if(divider) {
        look_ahead_time = (to_evader.magnitude() / divider);
    }

    // seek to the predicted future position of the evader
    actual_target = (evader->position + evader->velocity * look_ahead_time);

    // behaviours dont take ball height into account but 3d vector math does (otherwise -> flying players!)
    actual_target.z = 0;

    // this must always be called to advance the state!
    seek(actual_target);
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Intercept::OnEnd() {
    Locomotion::OnEnd();

    destination_reached = true;
    state_over = true;
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Intercept::StateOver() {
    return state_over;
}

// ------------------------------------------------------------
// Cancel
// ------------------------------------------------------------
void Intercept::Cancel() {
    state_over = true;
}

// --------------------------------------------------
// seek
// --------------------------------------------------
void Intercept::seek(GameLib::Vector3 _target) {
    player->velocity = _target - player->physical->position;
}

} // namespace SenselessSoccer

