#include "brain.h"

#include "../player.h"
#include "brainstate_idle.h"

namespace SenselessSoccer {

//  --------------------------------------------------
//  constructor
//  --------------------------------------------------
Brain::Brain(Player *p) : locomotion(p) {
    player = p;
    current_state = new BrainIdle(player);
}

//  --------------------------------------------------
//  Step
//  --------------------------------------------------
void Brain::Step(float dt) {
    GameLib::StateMachine::Step(dt);
    locomotion.UpdateLocomotion(dt);
}

bool Brain::in_pitch(float dt) {
    GameLib::Vector3 projected_position = player->project_position(dt);
    GameLib::Circle c(projected_position.x, projected_position.y, 20);
    GameLib::Rectangle r = player->pitch->metrics.pitch_rect;

    if (c.in_rect(r)) {
        return true;
    }

    return false;
}
} // namespace SenselessSoccer
