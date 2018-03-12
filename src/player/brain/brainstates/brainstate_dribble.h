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
 * @file brainstate_dribble.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */

#pragma once
#include "../../../metrics/metrics.h"
#include "brainstate.h"
#include <gamelib/utils/timer.h>
namespace SenselessSoccer {

class BrainDribble : public BrainState {
  public:
    /**
     * @brief BrainDribble
     * @param p
     */
    explicit BrainDribble(Player &p);

    /**
     * @brief OnStart
     */
    virtual void OnStart() override;

    /**
     * @brief OnStep
     * @param _dt
     */
    virtual void OnStep(const float _dt) override;

    /**
     * @brief OnEnd
     */
    virtual void OnEnd() override;

    /**
     * @brief StateOver
     * @return
     */
    virtual bool StateOver() override;

    /**
     * @brief init the dribble state
     * @param dir initial direction
     */
    void Init(Compass dir);

    /**
    * @brief modify the state parameters on the fly
    */
    virtual void Modify(modifier mod) override;

  protected:
    /**
     * @brief change_direction
     */
    void change_direction();
    int change_direction_ticker = 0;
    bool pass_timer_started = false;
    int pass_ticker = 0;
};
}

/*
 * The point of the dribble state is to run (physical ball dribbling happens
 * automatically) to a specified location, whilst
 * avoiding obstacles (other players)
 *
 * probable targets are:
 * - dribble to safety (eg defender)
 * - dribble to wing (eg winger looking for a cross)
 * - dribble to goal (eg midfielder looking for a through ball or striker looking for a
 * shoot
 *
 * there are only 2 possible obstacles:
 * - player
 * - pitch boundary
 *
 * there are a few possible stop conditions:
 * - reached destination
 * - ran into a dangerous position or situation (context sensetive)
 * - lost ball
 * - alternative excellent option becomes available
 */
