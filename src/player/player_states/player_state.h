#pragma once
#include <gamelib/statemachine/state.h>
#include "../../input/sensi_controller.h"

namespace SenselessSoccer {

/** @brief possible player states */
enum player_state { PLAYER_STATE_NONE, PLAYER_STATE_STAND, PLAYER_STATE_RUN, PLAYER_STATE_SLIDE };

class Player;
class PlayerState : public GameLib::State{

public:
    /**
    * @brief constructor
    * @param p reference to player for sm context
    */
    explicit PlayerState(Player &p);

    /**
    * @brief changeToNextState
    */
    virtual void ChangeToNextState() override;

    /**
     * @brief handle input events
     * @param event an event to handle
     */
    virtual bool HandleEvent(ControllerEvent event);

protected:
    /// for state machine context
    Player &player;

    /// next state
    player_state next_state;

    /**
     * @brief process input
     */
    virtual void handle_input();

public:
    friend class Player;
};

} // SenselessSoccer
