#include "brain.h"

#include "../player.h"
#include "brainstates/brainstate_cover.h"
#include "brainstates/brainstate_dribble.h"
#include "brainstates/brainstate_getball.h"
#include "brainstates/brainstate_idle.h"
#include "brainstates/brainstate_support.h"

namespace SenselessSoccer {

//  --------------------------------------------------
//  Brain
//  --------------------------------------------------
Brain::Brain(Player *p) : locomotion(p) {
    player = p;
    current_state = new BrainSupport(player);
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
    GameLib::Circle c(projected_position.x, projected_position.y, 50);
    GameLib::Rectangle r = player->pitch->metrics.pitch_rect;

    if(c.in_rect(r)) {
        return true;
    }

    return false;
}

// ------------------------------------------------------------
// ActivateState
// ------------------------------------------------------------
void Brain::ActivateState(brainstate bs) {
    ((BrainState*)(current_state))->next_state = bs;
    current_state->ChangeToNextState();
}

// ------------------------------------------------------------
// SetModifier
// ------------------------------------------------------------
void Brain::SetModifier(const modifier m) {
    if(current_state != nullptr) {
        ((BrainState *)(current_state))->Modify(m);
    }
}
} // namespace SenselessSoccer
