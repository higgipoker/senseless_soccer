/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file playere_state.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once
#include "../../joysticker/controller.h"
#include <gamelib/statemachine/state.h>

namespace SenselessSoccer {

/** @brief possible player states */
enum player_state {
    PLAYER_STATE_NONE,
    PLAYER_STATE_STAND,
    PLAYER_STATE_RUN,
    PLAYER_STATE_SLIDE
};

class Player;

/**
 * @brief The PlayerState class
 */
class PlayerState : public GameLib::State {

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
