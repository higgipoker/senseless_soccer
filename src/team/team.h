#pragma once

#include <gamelib/statemachine/state_machine.h>
#include <gamelib/game/game_entity.h>

#include "../player/player.h"

namespace SenselessSoccer{

class Team : public GameLib::StateMachine, public GameLib::GameEntity{
public:

	/**
	 * \brief constuct
	 */
	Team();

    /**
      \brief destruct
      */
    ~Team();

	/**
     * \brief on step
     * \param dt time delta
     */
    void Update(float dt);

	/**
	 * \brief add a player
	 * \param player pointer to player to add
	 */
	void AddPlayer( Player *player );

protected:

	/// players
	std::vector< Player* > players;
};

}// SenselessSoccer
