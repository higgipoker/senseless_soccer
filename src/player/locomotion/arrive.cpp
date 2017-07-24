#include "arrive.h"

namespace SenselessSoccer {

// --------------------------------------------------
// Arrive
// --------------------------------------------------
Arrive::Arrive(GameLib::Physical *physical) : Locomotion(physical) {
}

// --------------------------------------------------
// OnStart
// --------------------------------------------------
void Arrive::OnStart() {
	destination_reached = false;
	player->velocity = destination - player->position;
	last_distance = destination - player->position;
}

// --------------------------------------------------
// OnStep
// --------------------------------------------------
void Arrive::OnStep(const float dt) {
	GameLib::Vector3 new_distance = destination - player->position;

	if (player->position.equals(destination, 20)) {
		// reached destination?
		state_over = true;
		destination_reached = true;
		player->ResetVelocity();

	} else {
		// adjust for misses due to 45 degree precision
		if (new_distance.magnitude() <= last_distance.magnitude()) {
			player->velocity = destination - player->position;
		}
	}

	last_distance = destination - player->position;
}

// --------------------------------------------------
// OnEnd
// --------------------------------------------------
void Arrive::OnEnd() {
	destination = player->position;
	destination_reached = true;
	state_over = true;
}

// --------------------------------------------------
// StateOver
// --------------------------------------------------
bool Arrive::StateOver() {
	return state_over;
}

// --------------------------------------------------
// ChangeToNextState
// --------------------------------------------------
void Arrive::ChangeToNextState() {

}

// --------------------------------------------------
// Init
// --------------------------------------------------
void Arrive::Init(GameLib::Vector3 target) {
	destination = target;
}

}// namespace SenselessSoccer
