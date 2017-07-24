#pragma once

#include <gamelib/game/game_entity.h>
#include <gamelib/statemachine/state_machine.h>
#include "../ball/ball.h"
#include "../team/team.h"

namespace SenselessSoccer{

/** \brief match class */
class Match : public GameLib::StateMachine, public GameLib::GameEntity{

public:
	/**
	 * \brief constructor
	 */
	Match(){
		name = "match";
	}

	/// tmp ball pointer
	static Ball *ball;

private:

	/// a match has 2 teams
	Team team1, team2;

// ------------------------------------------------------------
// friends for state machine pattern
// ------------------------------------------------------------
public:
	friend class MatchState;
	friend class MatchStatePlay;
};

}// SenselessSoccer
