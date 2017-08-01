#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

/**
 * \brief locomotin to Cover at a locatin ("goto")
 */
class Cover : public Locomotion {

public:

    /**
     * \brief constructor
     * \param physical pointer to a physical object to move
     */
    Cover(GameLib::Physical *physical);

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
     * \brief init specific to Cover
     */
    void Init(GameLib::Vector3 target);

protected:

    GameLib::Vector3 last_distance;

};

}// namespace Senselesssoccer
