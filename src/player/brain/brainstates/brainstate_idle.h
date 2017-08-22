#pragma once

#include "../../player.h"
#include "brainstate.h"

namespace SenselessSoccer {

class BrainIdle : public BrainState {
public:
    /**
     * @brief BrainIdle
     * @param player
     */
    explicit BrainIdle(Player *player);

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
