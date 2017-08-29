#pragma once

#include "../../player.h"
#include "brainstate.h"

namespace SenselessSoccer {

/*
 * @brief ai state to make plyer go get a loose ball
 */
class BrainClear : public BrainState {
public:
    /**
     * @brief BrainClear
     * @param player pointer back to player for sm context
     */
    explicit BrainClear(Player *player);

    /**
     * @brief OnStart
     */
    virtual void OnStart() override;

    /**
     * @brief OnStep
     * @param _dt time delta
     */
    virtual void OnStep(const float _dt) override;

    /**
     * @brief OnEnd
     */
    virtual void OnEnd() override;

    /**
     * @brief StateOver
     */
    virtual bool StateOver() override;

};

}// namespace SenselessSoccer
