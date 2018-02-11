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
 * @file locomotion.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include <gamelib/math/vector3.h>
#include <string>
#include <vector>

namespace SenselessSoccer {

/// forward declaration
class Player;

/**
 * @brief base class for locomotion
 */
class Locomotion {
  public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player
     */
    explicit Locomotion(Player *p);

    /**
     * @brief ~Locomotion
     */
    virtual ~Locomotion();

    /**
     * @brief on state start
     */
    virtual void OnStart() = 0;

    /**
     * @brief on state step
     */
    virtual void OnStep(const float _dt) = 0;

    /**
     * @brief on state end
     */
    virtual void OnEnd() = 0;

    /**
     * @brief check if state end condition is met
     */
    virtual bool StateOver() = 0;

    /**
     * @brief some states can be ended manually
     */
    virtual void Cancel() = 0;

  protected:
    /// pointer back to player for state machine pattern
    Player *player;

    /// track if end condition is met
    bool state_over;

    /// track destination
    GameLib::Vector3 destination;

    /// hast he destination been reached?
    bool destination_reached;
};

} // namespace SenselessSoccer
