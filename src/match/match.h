#pragma once

#include "../ball/ball.h"
#include "../team/team.h"
#include <gamelib/game/game_entity.h>
#include <gamelib/statemachine/state_machine.h>

namespace SenselessSoccer {

/** @brief match class */
class Match : public GameLib::StateMachine {

public:
    /**
     * @brief constructor
     */
    Match (Team *t1, Team *t2) : team1 (*t1), team2 (*t2) {
        team1.other_team = &team2;
        team2.other_team = &team1;
    }

    /**
     * @brief Update
     */
    void Update (float dt) {
    }

    /// tmp ball pointer
    static Ball *ball;

private:
    /// a match has 2 teams
    Team &team1, &team2;

    // ------------------------------------------------------------
    // friends for state machine pattern
    // ------------------------------------------------------------
public:
    friend class MatchState;
    friend class MatchStatePlay;
};

} // SenselessSoccer
