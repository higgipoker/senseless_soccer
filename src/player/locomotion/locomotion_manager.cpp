#include "locomotion_manager.h"

#include "../player.h"

namespace SenselessSoccer {

LocomotionManager::LocomotionManager(Player *p) {
    player = p;
    behaviour = NULL;
    arrive = new Arrive(player);
    pursue = new Pursue(player);
    cover = new Cover(player);
}

LocomotionManager::~LocomotionManager() {
    delete arrive;
    delete pursue;
    delete cover;
}

void LocomotionManager::ActivateArrive(GameLib::Vector3 dest) {
    arrive->Init(dest);
    change_locomotion(arrive);
}

void LocomotionManager::ActivatePursue(GameLib::Physical *follow) {
    pursue->Init(follow);
    change_locomotion(pursue);
}

void LocomotionManager::ActivateCover() {
    change_locomotion(cover);
}

void LocomotionManager::UpdateLocomotion(float dt) {
    // check for pending behaviour
    if (!behaviour_queue.empty()) {
        Locomotion *next = behaviour_queue.back();
        behaviour_queue.pop();
        change_locomotion(next);
    }

    if (behaviour) {
        behaviour->OnStep(dt);

        if (behaviour->StateOver()) {
            behaviour->OnEnd();
            behaviour = NULL;
        }
    }
}

void LocomotionManager::SetLocomotion(Locomotion *l) {
    change_locomotion(l);
}

void LocomotionManager::change_locomotion(Locomotion *b) {
    if (b != nullptr) {

        // a behaviour is currently running
        if (behaviour) {
            // behaviours override the stop method, so some are not able to be stopped
            // manually
            behaviour->OnEnd();

            if (behaviour->StateOver()) {
                behaviour = b;

                if (behaviour) {
                    behaviour->OnStart();
                }
            } else {
                behaviour_queue.push(b);
            }
        } else {
            // no behaviour running
            behaviour = b;
            behaviour->OnStart();
        }
    } else {
        behaviour->OnEnd();
        behaviour = nullptr;
    }
}

void LocomotionManager::Cancel(void) {
    if (behaviour) {
        behaviour->OnEnd();
        behaviour = NULL;
    }
}

} // namespace SenselessSoccer
