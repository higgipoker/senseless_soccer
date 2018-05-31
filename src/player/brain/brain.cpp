/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file brain.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "brain.h"

#include "../player.h"
#include "brainstates/brainstate_support.h"

namespace SenselessSoccer {

// ControllerSimulator Brain::joystick;

//  --------------------------------------------------
//  Brain
//  --------------------------------------------------
Brain::Brain(Player &p) : locomotion(p), player(p) {
    current_state = new BrainSupport(player);
    current_state->OnStart();
}

//  --------------------------------------------------
//  Step
//  --------------------------------------------------
void Brain::Step(float dt) {
    GameLib::StateMachine::Step(dt);
    locomotion.UpdateLocomotion();
}

//  --------------------------------------------------
//  in_pitch
//  --------------------------------------------------
bool Brain::in_pitch(float dt) {
    GameLib::Circle c(player.physical.position.x, player.physical.position.y, 10);
    GameLib::Rectangle r = player.pitch->metrics.pitch_rect;

    if (c.in_rect(r)) {
        return true;
    }

    return false;
}

// ------------------------------------------------------------
// ActivateState
// ------------------------------------------------------------
void Brain::ActivateState(brainstate bs) {
    (static_cast<BrainState *>(current_state))->next_state = bs;
    current_state->ChangeToNextState();
}

// ------------------------------------------------------------
// SetModifier
// ------------------------------------------------------------
void Brain::SetModifier(const modifier m) {
    if (current_state != nullptr) {
        (static_cast<BrainState *>(current_state))->Modify(m);
    }
}

} // namespace SenselessSoccer
