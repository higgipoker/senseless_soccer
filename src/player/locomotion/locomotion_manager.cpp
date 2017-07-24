#include "locomotion_manager.h"

namespace SenselessSoccer {

LocomotionManager::LocomotionManager(GameLib::Physical *physical) {
	player = physical;
	behaviour = NULL;
// 	behaviour_cover = new Cover(player);
// 	behaviour_seek = new Seek(player);
// 	behaviour_heading = new Heading(player);
// 	behaviour_pursue = new Pursue(player);
// 	behaviour_intercept = new Intercept(player);
// 	behaviour_interpose = new Interpose(player);
// 	behaviour_goaltend = new Goaltend(player);
// 	behaviour_jump = new Jump(player);
// 	behaviour_dive = new Dive(player);
}

LocomotionManager::~LocomotionManager() {
// 	delete behaviour_cover;
// 	delete behaviour_seek;
// 	delete behaviour_heading;
// 	delete behaviour_pursue;
// 	delete behaviour_intercept;
// 	delete behaviour_interpose;
// 	delete behaviour_goaltend;
// 	delete behaviour_jump;
// 	delete behaviour_dive;
}

// //  --------------------------------------------------
// //  turnOnWandering
// //  --------------------------------------------------
// void LocomotionManager::TurnOnWandering(GameLib::Rectangle bounds) {}
//
// //  --------------------------------------------------
// //  turnOffWandering
// //  --------------------------------------------------
// void LocomotionManager::turnOffWandering() {}
//
// //  --------------------------------------------------
// //  turnOnSeeking
// //  --------------------------------------------------
// void LocomotionManager::turnOnSeeking(GameLib::Vector3 d) {
// 	Locomotion *pending_behaviour = behaviour_seek;
// 	behaviour_seek->init(d);
// 	changeLocomotion(pending_behaviour);
// }
//
// //  --------------------------------------------------
// //  turnOffSeeking
// //  --------------------------------------------------
// void LocomotionManager::turnOffSeeking() {
// 	turnOnCovering();
// }
//
// void LocomotionManager::turnOnHeading(GameLib::Vector3 d) {
// 	Locomotion *pending_behaviour = behaviour_heading;
// 	behaviour_heading->init(d);
//
// 	// special case for heading, don't stop and start if already running
// 	if (behaviour != pending_behaviour) {
// 		changeLocomotion(pending_behaviour);
// 	}
// }
//
// void LocomotionManager::turnOffHeading() {
// 	if (behaviour) {
// 		behaviour->stop();
// 	}
// }
//
// //  --------------------------------------------------
// //  turnOnPursuit
// //  --------------------------------------------------
// void LocomotionManager::turnOnPursuit(GameLib::PhysicalObject *t) {
// 	Locomotion *pending_behaviour = behaviour_pursue;
// 	behaviour_pursue->init(t);
// 	changeLocomotion(pending_behaviour);
// }
//
// //  --------------------------------------------------
// //  turnOffPursuit
// //  --------------------------------------------------
// void LocomotionManager::turnOffPursuit() {
// 	turnOnCovering();
// }
//
// //  --------------------------------------------------
// //  turnOnIntercept
// //  --------------------------------------------------
// void LocomotionManager::turnOnIntercept(GameLib::PhysicalObject *t) {
// 	Locomotion *pending_behaviour = behaviour_intercept;
// 	behaviour_intercept->Init(t);
// 	changeLocomotion(pending_behaviour);
// }
//
// //  --------------------------------------------------
// //  turnOffIntercept
// //  --------------------------------------------------
// void LocomotionManager::turnOffIntercept() {
// 	turnOnCovering();
// }
//
// //  --------------------------------------------------
// //  turnOnGoaltend
// //  --------------------------------------------------
// void LocomotionManager::turnOnGoaltend(
//     GameLib::PhysicalObject *defending_goal) {
// 	Locomotion *pending_behaviour = behaviour_goaltend;
// 	changeLocomotion(pending_behaviour);
// }
//
// //  --------------------------------------------------
// //  turnOffgoaltend
// //  --------------------------------------------------
// void LocomotionManager::turnOffGoaltend() {}
//
// //  --------------------------------------------------
// //  turnOnCovering
// //  --------------------------------------------------
// void LocomotionManager::turnOnCovering() {
// 	Locomotion *pending_behaviour = behaviour_cover;
// 	behaviour_cover->init(player->my_team->GetInstruction(
// 	                          TACTICS::INSTRUCTION_POSITIONING, player->role));
// 	change_locomotion(pending_behaviour);
// }
//
// //  --------------------------------------------------
// //  turnOffCovering
// //  --------------------------------------------------
// void LocomotionManager::turnOffCovering() {}
//
// //  --------------------------------------------------
// //  turnOnWaiting
// //  --------------------------------------------------
// void LocomotionManager::turnOnWaiting() {}
//
// //  --------------------------------------------------
// //  turnOffWaiting
// //  --------------------------------------------------
// void LocomotionManager::turnOffWaiting() {}
//
// //  --------------------------------------------------
// //  turnOnJump
// //  --------------------------------------------------
// void LocomotionManager::turnOnJump() {
// 	Locomotion *pending_behaviour = behaviour_jump;
// 	change_locomotion(pending_behaviour);
// }
//
// //  --------------------------------------------------
// //  turnOffJump
// //  --------------------------------------------------
// void LocomotionManager::turnOffJump() {}
//
// //  --------------------------------------------------
// //  turnOnDive
// //  --------------------------------------------------
// void LocomotionManager::turnOnDive(const GameLib::Point &_interesect) {
// 	Locomotion *pending_behaviour = behaviour_dive;
// 	behaviour_dive->init(_interesect);
// 	change_locomotion(pending_behaviour);
// }
//
// //  --------------------------------------------------
// //  turnOffDive
// //  --------------------------------------------------
// void LocomotionManager::turnOffDive() {}

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
