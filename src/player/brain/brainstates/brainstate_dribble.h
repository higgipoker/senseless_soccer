#pragma once
#include "brainstate.h"
#include <gamelib/utils/timer.h>
#include "../../../metrics/metrics.h"
namespace SenselessSoccer {

class BrainDribble : public BrainState {
public:
    /**
     * @brief BrainDribble
     * @param p
     */
    BrainDribble(Player *p);

    /**
     * @brief OnStart
     */
    virtual void OnStart() override;

    /**
     * @brief OnStep
     * @param _dt
     */
    virtual void OnStep(const float _dt) override;

    /**
     * @brief OnEnd
     */
    virtual void OnEnd() override;

    /**
     * @brief StateOver
     * @return
     */
    virtual bool StateOver() override;

    /**
     * @brief init the dribble state
     * @param dir initial direction
     */
    void Init(Compass dir);

     /**
     * @brief modify the state parameters on the fly
     */
    virtual void Modify(modifier mod) override;

protected:
    /**
     * @brief change_direction
     */
    void change_direction();
    GameLib::Timer timer;
};
}

/*
 * The point of the dribble state is to run (physical ball dribbling happens automatically) to a specified location, whilst
 * avoiding obstacles (other players)
 *
 * probable targets are:
 * - dribble to safety (eg defender)
 * - dribble to wing (eg winger looking for a cross)
 * - dribble to goal (eg midfielder looking for a through ball or striker looking for a shoot
 *
 * there are only 2 possible obstacles:
 * - player
 * - pitch boundary
 *
 * there are a few possible stop conditions:
 * - reached destination
 * - ran into a dangerous position or situation (context sensetive)
 * - lost ball
 * - alternative excellent option becomes available
 */
