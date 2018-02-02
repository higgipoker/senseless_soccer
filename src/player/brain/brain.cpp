#include "brain.h"

#include "../player.h"
#include "brainstates/brainstate_support.h"


namespace SenselessSoccer {

//  --------------------------------------------------
//  Brain
//  --------------------------------------------------
Brain::Brain(Player *p) : locomotion(p) {
    player = p;
    current_state = new BrainSupport(player);
    current_state->OnStart();
}

//  --------------------------------------------------
//  Step
//  --------------------------------------------------
void Brain::Step(double dt) {
    GameLib::StateMachine::Step(dt);
    locomotion.UpdateLocomotion(dt);
}

//  --------------------------------------------------
//  in_pitch
//  --------------------------------------------------
bool Brain::in_pitch(double dt) {
    GameLib::Vector3 projected_position = player->project_position(dt);
    GameLib::Circle c(projected_position.x, projected_position.y, 10);
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
    (static_cast<BrainState*>(current_state))->next_state = bs;
    current_state->ChangeToNextState();
}

// ------------------------------------------------------------
// SetModifier
// ------------------------------------------------------------
void Brain::SetModifier(const modifier m) {
    if(current_state != nullptr) {
       (static_cast<BrainState*>(current_state))->Modify(m);
    }
}
} // namespace SenselessSoccer
