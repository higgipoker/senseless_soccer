#include "head.h"

#include "../player.h"
#include <gamelib/utils/log.h>

namespace SenselessSoccer {

// ------------------------------------------------------------
// Head
// ------------------------------------------------------------
Head::Head(Player *p) : Locomotion(p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Head::OnStart() {
    state_over = false;
    player->velocity = direction;
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Head::OnStep(const float dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Head::OnEnd() {
    Locomotion::OnEnd();

    player->physical->ResetVelocity();
    state_over = true;
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Head::StateOver() {
    return state_over;
}

// ------------------------------------------------------------
// Init
// ------------------------------------------------------------
void Head::Init(GameLib::Vector3 dir) {
    direction = dir;
    direction.normalizeToUnits();
}

// ------------------------------------------------------------
// Cancel
// ------------------------------------------------------------
void Head::Cancel(){
    state_over = true;
}

} // namespace SenselessSoccer
