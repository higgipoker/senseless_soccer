#pragma once
#include <gamelib/statemachine/state.h>
namespace SenselessSoccer {

/** \brief possible player states */
enum player_state {
    PLAYER_STATE_NONE,
    PLAYER_STATE_STAND,
    PLAYER_STATE_RUN
};

class Player;
class PlayerState : public GameLib::State {

public:

    /**
    * \brief constructor
	* \param p reference to player for sm context
    */
    explicit PlayerState(Player &p);

    /**
    * \brief changeToNextState
    */
    virtual void ChangeToNextState() override;

protected:
	/// for state machine context
    Player &player;

	/// next state
	player_state next_state;
};

}// SenselessSoccer
