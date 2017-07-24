#include "team.h"

#include "team_states/team_play.h"

namespace SenselessSoccer {
// ------------------------------------------------------------
// Construct
// ------------------------------------------------------------
Team::Team(){
	name = "team";
	InitState(new TeamStatePlay());
	current_state->OnStart();
}
// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Team::Update(float dt) {

	// base entity
	GameLib::GameEntity::Update(dt);

    // advance state machine
    GameLib::StateMachine::Step(dt);
}

// ------------------------------------------------------------
// AddPlayer
// ------------------------------------------------------------
void Team::AddPlayer( Player *player){
	players.push_back( player );
}

}// SenselessSoccer
