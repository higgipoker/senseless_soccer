#pragma once
#include "controller.h"
#include "simulated_actions/simulated_action.h"
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
	ControllerSimulator(void);

	/**
	 * @brief Update
	 */
	void Update();

  protected:
	SimulatedAction *current_action;
};

} // namespace SenselessSocccer
