#include "pursue.h"

namespace SenselessSoccer {

// --------------------------------------------------
// Pursue
// --------------------------------------------------
Pursue::Pursue(GameLib::Physical *physical) : Locomotion(physical) {}

// --------------------------------------------------
// OnStart
// --------------------------------------------------
void Pursue::OnStart() {
  state_over = false;
  destination_reached = false;
}

// --------------------------------------------------
// OnStep
// --------------------------------------------------
void Pursue::OnStep(const float dt) {
  if (destination_reached) return;

  player->velocity = target->position - player->position;
  last_distance = target->position - player->position;
  GameLib::Vector3 new_distance = target->position - player->position;

  if (player->position.equals(destination, 5)) {
    destination_reached = true;
    player->ResetVelocity();

  } else {
    if (new_distance.magnitude() > last_distance.magnitude()) {
      player->velocity = target->position - player->position;
    }
  }

  last_distance = target->position - player->position;
}

// --------------------------------------------------
// OnEnd
// --------------------------------------------------
void Pursue::OnEnd() {
  destination_reached = true;
  state_over = true;
}

// --------------------------------------------------
// StateOver
// --------------------------------------------------
bool Pursue::StateOver() { return state_over; }

// --------------------------------------------------
// ChangeToNextState
// --------------------------------------------------
void Pursue::ChangeToNextState() {}

// --------------------------------------------------
// Init
// --------------------------------------------------
void Pursue::Init(GameLib::Physical *t) { target = t; }

}  // namespace SenselessSoccer
