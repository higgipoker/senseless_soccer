#include "standing.h"
#include "../player.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Standing::Standing (Player &p) : PlayerState (p) {
}


// ------------------------------------------------------------
// OnStart
// ------------------------------------------------------------
void Standing::OnStart() {
	player.player_sprite->SetAnimation ("stand_south");
}

// ------------------------------------------------------------
// OnStep
// ------------------------------------------------------------
void Standing::OnStep (const float dt) {
}

// ------------------------------------------------------------
// OnEnd
// ------------------------------------------------------------
void Standing::OnEnd() {}

// ------------------------------------------------------------
// StateOver
// ------------------------------------------------------------
bool Standing::StateOver() {

	if (player.physical->velocity.magnitude()) {
		next_state = PLAYER_STATE_RUN;
		return true;
	}

	return false;
}

}// SenselessSoccer
