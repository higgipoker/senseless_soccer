#include "locomotion.h"
#include <iostream>

namespace SenselessSoccer {

// --------------------------------------------------
// Locomotion
// --------------------------------------------------
Locomotion::Locomotion(GameLib::Physical *physical) {
	player = physical;
	state_over = false;
	destination_reached = false;
}

// --------------------------------------------------
// ~Locomotion
// --------------------------------------------------
Locomotion::~Locomotion(void) {}

// --------------------------------------------------
// start
// --------------------------------------------------
void Locomotion::OnStart(void) {
	state_over = false;
}

// --------------------------------------------------
// step
// --------------------------------------------------
void Locomotion::OnStep(float _dt) {
}

// --------------------------------------------------
// stop
// --------------------------------------------------
void Locomotion::OnEnd(void) {
}

}  // namespace SenselessSoccer

