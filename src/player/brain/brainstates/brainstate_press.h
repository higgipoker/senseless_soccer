#pragma once

#include "../../player.h"
#include "brainstate.h"

namespace SenselessSoccer {

/*
 * ai state to make plyer go get a loose ball
 */
class BrainPress : public BrainState {
  public:
    /**
     * @brief BrainPress
     * @param player
     */
    explicit BrainPress(Player &player);

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

  protected:
};
}
