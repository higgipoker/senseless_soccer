#pragma once
#include "../p1/controller.h"
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
	  * @brief Update
	  */
	void Update();

  protected:
	/// current action to execute
	SimulatedAction *current_action;
};

} // namespace SenselessSocccer
