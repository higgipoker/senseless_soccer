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
 * @file controller_simulator.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once
#include "../controller.h"
#include "simulated_actions/simulate_nothing.h"
#include <vector>

namespace SenselessSoccer {

/**
 * @brief The ControllerEmulator class
 */
class ControllerSimulator : public Controller {
  public:
    /**
      * @brief constructor
      */
    ControllerSimulator();

    /**
      * @brief destruct
      */
    ~ControllerSimulator();

    /**
      * @brief update method to poll
      */
    void Update();

    /// only attach to one player at a time!
    bool is_attached = false;

  protected:
    /// current action to execute
    SimulatedSequence *current_sequence;

    /// for timing
    int ticks = 0;

    /// track when to start the action timer
    bool first_action;
};

} // namespace SenselessSocccer
