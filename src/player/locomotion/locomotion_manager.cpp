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
 * @file locomotion_manager.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "locomotion_manager.h"
#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// LocomotionManager
// ------------------------------------------------------------
LocomotionManager::LocomotionManager(Player *p)
    : player(*p), arrive(&player), pursue(&player), head(&player), intercept(&player) {
    behaviour = nullptr;
}

// ------------------------------------------------------------
// ActivateArrive
// ------------------------------------------------------------
void LocomotionManager::ActivateArrive(GameLib::Vector3 dest) {
    arrive.Init(dest);
    change_locomotion(arrive);
}

// ------------------------------------------------------------
// ActivatePursue
// ------------------------------------------------------------
void LocomotionManager::ActivatePursue(GameLib::Physical *follow) {
    pursue.Init(follow);
    change_locomotion(pursue);
}

// ------------------------------------------------------------
// ActivateHead
// ------------------------------------------------------------
void LocomotionManager::ActivateHead(GameLib::Vector3 dir) {
    head.Init(dir);
    change_locomotion(head);
}

// ------------------------------------------------------------
// ActivateIntercept
// ------------------------------------------------------------
void LocomotionManager::ActivateIntercept(GameLib::Physical *follow) {
    intercept.Init(follow);
    change_locomotion(intercept);
}

// ------------------------------------------------------------
// UpdateLocomotion
// ------------------------------------------------------------
void LocomotionManager::UpdateLocomotion(float dt) {
    // check for pending behaviour
    if (!behaviour_queue.empty()) {
        Locomotion *next = behaviour_queue.back();
        behaviour_queue.pop();
        change_locomotion(*next);
    }

    if (behaviour) {
        behaviour->OnStep(dt);

        if (behaviour->StateOver()) {
            behaviour->OnEnd();
            behaviour = NULL;
        }
    }
}

// ------------------------------------------------------------
// change_locomotion
// ------------------------------------------------------------
void LocomotionManager::change_locomotion(Locomotion &b) {

    // a behaviour is currently running
    if (behaviour) {
        // behaviours override the cancel method, so some are not able to be stopped
        // manually
        behaviour->Cancel();

        if (behaviour->StateOver()) {
            behaviour = &b;

            if (behaviour) {
                behaviour->OnStart();
            }

        } else {
            behaviour_queue.push(&b);
        }

    } else {
        // no behaviour running
        behaviour = &b;
        behaviour->OnStart();
    }
}

// ------------------------------------------------------------
// Cancel
// ------------------------------------------------------------
void LocomotionManager::Cancel(void) {
    if (behaviour) {
        behaviour->OnEnd();
        behaviour = NULL;
    }
}

} // namespace SenselessSoccer
