#pragma once
#include "brainstate.h"
#include <gamelib/utils/timer.h>
#include "../../../metrics/metrics.h"
namespace SenselessSoccer {

class BrainPass : public BrainState {
public:
    /**
     * @brief BrainPass
     * @param p
     */
    BrainPass(Player *p);

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
    void Init(Player *receiver);

     /**
     * @brief modify the state parameters on the fly
     */
    virtual void Modify(modifier mod) override;

protected:

};
}

