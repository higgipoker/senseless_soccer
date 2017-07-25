#include "locomotion_manager.h"

namespace SenselessSoccer {

LocomotionManager::LocomotionManager(GameLib::Physical *physical) {
	player = physical;
	behaviour = NULL;
	arrive = new Arrive(player);
	pursue = new Pursue(player);
}

LocomotionManager::~LocomotionManager() {
	delete arrive;
	delete pursue;
}

//  --------------------------------------------------
//  ActivateArrive
//  --------------------------------------------------
void LocomotionManager::ActivateArrive(GameLib::Vector3 dest){

	arrive->Init(dest);
	change_locomotion(arrive);
}

//  --------------------------------------------------
//  ActivatePursue
//  --------------------------------------------------
void LocomotionManager::ActivatePursue(GameLib::Physical *follow){

	pursue->Init(follow);
	change_locomotion(pursue);
}

//  --------------------------------------------------
//  updateLocomotion
//  --------------------------------------------------
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

//  --------------------------------------------------
//  SetLocomotion
//  --------------------------------------------------
void LocomotionManager::SetLocomotion(Locomotion *l){
	change_locomotion(l);
}

//  --------------------------------------------------
//  change_locomotion
//  --------------------------------------------------
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
	}else{
		behaviour->OnEnd();
		behaviour = nullptr;
	}
}

//  --------------------------------------------------
//  Cancel
//  --------------------------------------------------
void LocomotionManager::Cancel(void) {
	if (behaviour) {
		behaviour->OnEnd();
		behaviour = NULL;
	}
}

}  // namespace SenselessSoccer
