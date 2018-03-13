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
 * @file arrive.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

/**
 * @brief Like a "goto" instruction
 *          the player simply runs to the specified destination
 *          and then stops.
 */
class Arrive : public Locomotion {

  public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player
     */
    explicit Arrive(Player &p);

    /**
     * @brief ~Arrive
     */
    virtual ~Arrive() {}

    /**
     * @brief state on start
     */
    virtual void OnStart() override;

    /**
     * @brief state on step
     */
    virtual void OnStep() override;

    /**
     * @brief state on end
     */
    virtual void OnEnd() override;

    /**
     * @brief state check if finished
     */
    virtual bool StateOver() override;

    /**
     * @brief init the state
     */
    void Init(GameLib::Vector3 target);

    /**
     * @brief some states can be ended manually
     */
    virtual void Cancel() override;

  protected:
    /// tracks last distance from target destination
    GameLib::Vector3 last_distance;
};

} // namespace Senselesssoccer
