#pragma once

#include "player_state.h"

namespace SenselessSoccer {

class Running : public PlayerState {

public:
    /**
    * @brief constructor
    * @param p reference to player for sm context
    */
    explicit Running(Player &p);

    /**
     * @brief onStart
     */
    virtual void OnStart() override;

    /**
     * @brief onStep
     * @param dt time delta
     */
    virtual void OnStep(const float dt) override;

    /**
     * @brief onEnd
     */
    virtual void OnEnd() override;

    /**
     * @brief stateOver
     */
    virtual bool StateOver() override;

    /**
     * @brief stateName
     */
    std::string StateName() const {
        return name;
    }

protected:
};

} // SenselessSoccer
