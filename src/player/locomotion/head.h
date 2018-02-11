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
 * @file head.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

/**
 * @brief player runs in a specific direction until state is stopped
 */
class Head : public Locomotion {
  public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player for state machine context
     */
    explicit Head(Player *p);

    /**
     * @brief ~Head
     */
    virtual ~Head() {}

    /**
     * @brief state start
     */
    virtual void OnStart() override;

    /**
     * @brief state step
     * @param [in] dt time delta
     */
    virtual void OnStep(const float dt) override;

    /**
     * @brief state end
     */
    virtual void OnEnd() override;

    /**
     * @brief check for end condition
     */
    virtual bool StateOver() override;

    /**
     * @brief init the state
     * @param [in] dir direction
     */
    void Init(GameLib::Vector3 dir);

    /**
     * @brief some states can be ended manually
     */
    virtual void Cancel() override;

  protected:
    GameLib::Vector3 direction;
};

} // namespace Senselesssoccer
