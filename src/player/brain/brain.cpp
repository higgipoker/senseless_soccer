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

    if (c.in_rect(r)) {
        return true;
    }

    return false;
}

// ------------------------------------------------------------
// ActivateState
// ------------------------------------------------------------
void Brain::ActivateState(brainstate bs) {

    switch (bs) {
    default:
    case BRAINSTATE_NONE:
        break;
    case BRAIN_COVER:
        ChangeState(new BrainCover(player));
        break;
    case BRAIN_DRIBBLE:
        ChangeState(new BrainDribble(player));
        break;
    case BRAIN_GETBALL:
        ChangeState(new BrainGetBall(player));
        break;
    case BRAIN_IDLE:
        ChangeState(new BrainIdle(player));
        break;
    case BRAIN_SUPPORT:
        ChangeState(new BrainSupport(player));
        break;
    }
}

// ------------------------------------------------------------
// SetModifier
// ------------------------------------------------------------
void Brain::SetModifier(const modifier m) {
    if (current_state != nullptr) {
        ((BrainState *)(current_state))->Modify(m);
    }
}
} // namespace SenselessSoccer
