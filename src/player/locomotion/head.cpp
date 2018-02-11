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
 * @file head.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "head.h"

#include "../player.h"
#include <gamelib/utils/log.h>

namespace SenselessSoccer {

// ------------------------------------------------------------
// Head
// ------------------------------------------------------------
Head::Head(Player *p) : Locomotion(p) {}

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
void Head::OnStep(const float dt) {}

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
bool Head::StateOver() { return state_over; }

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
void Head::Cancel() { state_over = true; }

} // namespace SenselessSoccer
