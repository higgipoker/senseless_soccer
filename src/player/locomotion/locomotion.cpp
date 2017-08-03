#include "locomotion.h"

#include <iostream>

#include "../player.h"

namespace SenselessSoccer {

Locomotion::Locomotion(Player *p) {
    player = p;
    state_over = false;
    destination_reached = false;
    modifier = NONE;
}

Locomotion::~Locomotion(void) {}

void Locomotion::OnStart(void) { state_over = false; }

void Locomotion::OnStep(float _dt) {}

void Locomotion::OnEnd(void) {}

} // namespace SenselessSoccer
