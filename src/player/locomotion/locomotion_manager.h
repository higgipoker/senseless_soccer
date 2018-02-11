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
 * @file locomotion_manager.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "arrive.h"
#include "head.h"
#include "intercept.h"
#include "pursue.h"
#include <gamelib/statemachine/state_machine.h>
#include <queue>

namespace SenselessSoccer {

class Player;
class LocomotionManager : public GameLib::StateMachine {
  public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player for state machine context
     */
    explicit LocomotionManager(Player *p);

    /**
     * @brief update
     * @param [in] dt time delta
     */
    void UpdateLocomotion(float dt);

    /**
     * @brief activate the arrive locomotion
     */
    void ActivateArrive(GameLib::Vector3 dest);

    /**
     * @brief activate the pursue locomotion
     */
    void ActivatePursue(GameLib::Physical *follow);

    /**
     * @brief activate the head locomotion
     */
    void ActivateHead(GameLib::Vector3 dir);

    /**
     * @brief activate the intercept locomotion
     */
    void ActivateIntercept(GameLib::Physical *follow);

    /**
     * @brief cancel all locomotion
     */
    void Cancel(void);

  private:
    /// ref back to player
    Player &player;

    /// current locomition behaviour
    Locomotion *behaviour;

    /// an arrive behaviour
    Arrive arrive;

    /// a pursue locomotion
    Pursue pursue;

    ///  a head ocomotion
    Head head;

    // an intercept behaviour
    Intercept intercept;

    /// locomotion queue
    std::queue<Locomotion *> behaviour_queue;

    /// helper to change locomotion
    void change_locomotion(Locomotion &b);
};

} // namespace SenselessSoccer
