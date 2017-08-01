#include "team.h"

#include "team_states/team_play.h"

namespace SenselessSoccer {
// ------------------------------------------------------------
// Construct
// ------------------------------------------------------------
Team::Team(){
	name = "team";
    physical = new GameLib::Physical();
    renderable = new GameLib::Renderable();
	InitState(new TeamStatePlay());
	current_state->OnStart();
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Team::~Team(){
    delete physical;
    delete renderable;
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
