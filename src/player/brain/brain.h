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
 * @file brain.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "../../joysticker/cpu/controller_simulator.h"
#include "../locomotion/locomotion_manager.h"
#include <gamelib/statemachine/state_machine.h>

namespace SenselessSoccer {

/** @brief all possible brainstates */
enum brainstate {
    BRAIN_NONE,
    BRAIN_COVER,
    BRAIN_DRIBBLE,
    BRAIN_GETBALL,
    BRAIN_IDLE,
    BRAIN_SUPPORT,
    BRAIN_PASS,
    BRAIN_RECEIVE,
    BRAIN_SHOOT,
    BRAIN_PRESS,
    BRAIN_CLEAR
};

/** @brief all possible modifier types */
enum modifier {
    MODIFIER_NONE,
    COVER_PRESS,
    COVER_PRESS_HIGH,
    COVER_SHADOW,
    COVER_SHADOW_DEEP,
    SUPPORT_PASS,
    SUPPORT_BACKUP,
    SUPPORT_RUN,
    DRIBBLE_CHANGE_DIRECTION,
};

class Player;
class Brain : public GameLib::StateMachine {
  public:
    /**
     * @brief Brain
     * @param p pointer back to player
     */
    explicit Brain(Player &p);

    /**
     * @brief Step
     * @param dt time delta
     */
    void Step(float dt);

    /**
      * @brief activate a brain state manually
      */
    void ActivateState(brainstate bs);

    /**
      * @brief set a locomotion modifier
      * @param [in] m modifier type
      */
    void SetModifier(const modifier m);

    /// locomotio manager
    LocomotionManager locomotion;

    /// a debug string
    std::string statename;

  protected:
    /// pointer back to player for sm context
    Player &player;

    /// brain states need a joysticker to execute their ideas, just like players
    static ControllerSimulator joystick;

    /// is the playe rin the pitch
    bool in_pitch(float dt);

  public:
    friend class BrainDribble;
};

} // namespace SenselessSoccer
