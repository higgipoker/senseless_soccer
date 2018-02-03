#pragma once
#include "../controller.h"
#include "simulated_actions/simulate_nothing.h"
#include <SFML/System.hpp>
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

protected:
    /// current action to execute
    SimulatedSequence *current_sequence;

    /// for timing
    sf::Clock timer;

    /// track when to start the action timer
    bool first_action;

    /// debug
    bool log = true;
};

} // namespace SenselessSocccer
