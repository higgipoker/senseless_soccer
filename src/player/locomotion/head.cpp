#include "head.h"

#include "../player.h"
#include <gamelib/utils/log.h>

namespace SenselessSoccer {

Head::Head(Player *p) : Locomotion(p) {
}

void Head::OnStart() {
    state_over = false;
    player->physical->velocity = direction;
}

void Head::OnStep(const float dt) {
}

void Head::OnEnd() {
    player->physical->ResetVelocity();
    state_over = true;
}

bool Head::StateOver() {
    return state_over;
}

void Head::ChangeToNextState() {
}

void Head::Modify(Modifier mod) {
    modifier = mod;
}

void Head::Init(GameLib::Vector3 dir) {
    direction = dir;
    direction.normalizeToUnits();
}

} // namespace SenselessSoccer
