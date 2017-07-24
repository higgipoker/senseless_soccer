#pragma once

#include <gamelib/statemachine/state_machine.h>
#include "../locomotion/locomotion_manager.h"

namespace SenselessSoccer {
class Player;
class Brain : public GameLib::StateMachine {
public:

	/**
	 * \brief constructor
	 * \param p pointer to player
	 */
	Brain(Player *p);

	/**
     * \brief on step
     * \param dt time delta
     */
    void Step(float dt);

	/// brain manages locomotion
	LocomotionManager locomotion;

private:

	/// pointer back to player
	Player *player;

};

}// namespace SenselessSoccer
