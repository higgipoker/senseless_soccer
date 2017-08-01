#include "cover.h"

namespace SenselessSoccer {

// --------------------------------------------------
// Cover
// --------------------------------------------------
Cover::Cover(GameLib::Physical *physical) : Locomotion(physical) {}

// --------------------------------------------------
// OnStart
// --------------------------------------------------
void Cover::OnStart() {
  state_over = false;
  destination_reached = false;
}

// --------------------------------------------------
// OnStep
// --------------------------------------------------
void Cover::OnStep(const float dt) {
}

// --------------------------------------------------
// OnEnd
// --------------------------------------------------
void Cover::OnEnd() {
  destination = player->position;
  destination_reached = true;
  state_over = true;
}

// --------------------------------------------------
// StateOver
// --------------------------------------------------
bool Cover::StateOver() { return state_over; }

// --------------------------------------------------
// ChangeToNextState
// --------------------------------------------------
void Cover::ChangeToNextState() {}

// --------------------------------------------------
// Init
// --------------------------------------------------
void Cover::Init(GameLib::Vector3 target) { destination = target; }

}  // namespace SenselessSoccer
