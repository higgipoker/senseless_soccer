#include "locomotion_manager.h"

#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// LocomotionManager
// ------------------------------------------------------------
LocomotionManager::LocomotionManager(Player *p) : player(*p), arrive(&player), pursue(&player), head(&player) {
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
// UpdateLocomotion
// ------------------------------------------------------------
void LocomotionManager::UpdateLocomotion(float dt) {
    // check for pending behaviour
    if(!behaviour_queue.empty()) {
        Locomotion *next = behaviour_queue.back();
        behaviour_queue.pop();
        change_locomotion(*next);
    }

    if(behaviour) {
        behaviour->OnStep(dt);

        if(behaviour->StateOver()) {
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
    if(behaviour) {
        // behaviours override the cancel method, so some are not able to be stopped
        // manually
        behaviour->Cancel();

        if(behaviour->StateOver()) {
            behaviour = &b;

            if(behaviour) {
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
    if(behaviour) {
        behaviour->OnEnd();
        behaviour = NULL;
    }
}

} // namespace SenselessSoccer
