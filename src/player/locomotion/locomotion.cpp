#include "locomotion.h"

#include <iostream>

#include "../player.h"

namespace SenselessSoccer {

// --------------------------------------------------
// Locomotion
// --------------------------------------------------
Locomotion::Locomotion(Player *p) {
    player = p;
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

