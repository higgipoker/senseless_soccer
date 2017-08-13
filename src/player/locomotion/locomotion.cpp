#include "locomotion.h"

#include <iostream>

#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Locomotion
// ------------------------------------------------------------
Locomotion::Locomotion(Player *p) {
    player = p;
    state_over = false;
    destination_reached = false;
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Locomotion::OnStart(void) {
    state_over = false;
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Locomotion::OnStep(float _dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Locomotion::OnEnd(void) {
}

} // namespace SenselessSoccer
