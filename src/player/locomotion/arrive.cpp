#include "arrive.h"

#include "../player.h"

namespace SenselessSoccer {

// --------------------------------------------------
// Arrive
// --------------------------------------------------
Arrive::Arrive(Player *p) : Locomotion(p) {}

// --------------------------------------------------
// OnStart
// --------------------------------------------------
void Arrive::OnStart() {
  state_over = false;
  destination_reached = false;
  player->physical->velocity = destination - player->physical->position;
  last_distance = destination - player->physical->position;
}

// --------------------------------------------------
// OnStep
// --------------------------------------------------
void Arrive::OnStep(const float dt) {
  GameLib::Vector3 new_distance = destination - player->physical->position;

  if (player->physical->position.equals(destination, 20)) {
    // reached destination?
    state_over = true;
    destination_reached = true;
    player->physical->ResetVelocity();

  } else {
    // adjust for misses due to 45 degree precision
    if (new_distance.magnitude() <= last_distance.magnitude()) {
      player->physical->velocity = destination - player->physical->position;
    }
  }

  last_distance = destination - player->physical->position;
}

// --------------------------------------------------
// OnEnd
// --------------------------------------------------
void Arrive::OnEnd() {
  destination = player->physical->position;
  destination_reached = true;
  state_over = true;
}

// --------------------------------------------------
// StateOver
// --------------------------------------------------
bool Arrive::StateOver() { return state_over; }

// --------------------------------------------------
// ChangeToNextState
// --------------------------------------------------
void Arrive::ChangeToNextState() {}

// --------------------------------------------------
// Init
// --------------------------------------------------
void Arrive::Init(GameLib::Vector3 target) { destination = target; }

}  // namespace SenselessSoccer
