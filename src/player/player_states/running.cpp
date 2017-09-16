#include "running.h"

#include "../player.h"
#include <gamelib/physics/collision_detector.h>

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Running::Running(Player &p)
 : PlayerState(p) {
}

// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Running::OnStart() {
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Running::OnStep(const float dt) {
	// set the animation based on velocity (running direction)
	player.player_sprite->SetRunningAnimation(player.velocity.roundAngle(45));

	// check for collision with ball (dribble)
	if (GameLib::CollisionDetector::collision(player.dribble_circle, player.ball->GetCollidable())) {
		player.do_dribble(player.velocity.normalised());
	}
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Running::OnEnd() {
}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Running::StateOver() {
	if (player.velocity.magnitude() == 0) {
		next_state = PLAYER_STATE_STAND;
		return true;

	} else if (player.sliding == true) {
		next_state = PLAYER_STATE_SLIDE;
		return true;
	}

	return false;
}

bool Running::HandleEvent(ControllerEvent event) {

	if (!PlayerState::HandleEvent(event)) {

		switch (event.id) {

		case FIRE_PRESS:
			if (!player.sliding) {
				if (!player.ball_under_control()) {
					player.DoSlideTackle();
					return true;
				}
			}

			break;

		case FIRE_RELEASE:
			break;

		case FIRE_TAP:
			break;

		case FIRE_DOUBLE_TAP:
			break;

		case NO_EVENT:
		default:
			break;
		}
	}

	return false;
}

} // SenselessSoccer
