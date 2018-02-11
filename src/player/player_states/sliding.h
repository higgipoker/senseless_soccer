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
 * @file sliding.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "player_state.h"
#include <gamelib/math/vector3.h>
#include <gamelib/utils/timer.h>

namespace SenselessSoccer {

class Sliding : public PlayerState {

  public:
    /**
    * @brief constructor
    * @param p reference to player for sm context
    */
    explicit Sliding(Player &p);

    /**
     * @brief onStart
     */
    virtual void OnStart() override;

    /**
     * @brief onStep
     * @param dt time delta
     */
    virtual void OnStep(const float dt) override;

    /**
     * @brief onEnd
     */
    virtual void OnEnd() override;

    /**
     * @brief stateOver
     */
    virtual bool StateOver() override;

    /**
     * @brief stateName
     */
    std::string StateName() const { return name; }

  protected:
    /**
     * @brief process input
     */
    virtual void handle_input() override;

    /// slide direction
    GameLib::Vector3 dir;

    /// to track distance
    GameLib::Vector3 start;

    /// some time at the end to get up
    bool getting_up = false;

    /// time the get up time
    int down_frames = 0;
};

} // SenselessSoccer
