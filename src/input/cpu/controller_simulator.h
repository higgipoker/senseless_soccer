#pragma once
#include "../p1/controller.h"
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
	  * @brief Update
	  */
	void Update();

  protected:
	/// current action to execute
    SimulatedSequence *current_action;

    /// for timing
    sf::Clock timer;

    /// track when to set timer first time
    bool first_action;

    /// debug
    bool log = true;
};

} // namespace SenselessSocccer
