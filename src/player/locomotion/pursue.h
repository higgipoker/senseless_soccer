#pragma once

#include <gamelib/physics/physical.h>
#include "locomotion.h"

namespace SenselessSoccer{

/** \brief "chase after" behaviour
  */
class Pursue : public Locomotion{
public:

	/**
	 * \brief constructor
	 * \param physical pointer to a physical object to move
	 */
    Pursue(Player *p);

	/**
	* \brief onStart
	*/
	virtual void OnStart();

	/**
	 * \brief onStep
	 * \param dt time delta
	 */
	virtual void OnStep(const float dt);

	/**
	 * \brief onEnd
	 */
	virtual void OnEnd();

	/**
	 * \brief stateOver
	 */
	virtual bool StateOver();

	/**
	 * \brief changeToNextState
	 */
	virtual void ChangeToNextState();

	/**
	 * \brief init specific to arrive
	 */
	void Init(GameLib::Physical *t);

    protected:

    /// physical entity to pursue
    GameLib::Physical *target;

    GameLib::Vector3 last_distance;
    };
}
