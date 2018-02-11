#pragma once

#include "player_state.h"
#include <gamelib/math/vector3.h>
#include <gamelib/utils/timer.h>

namespace SenselessSoccer {

class Sliding : public PlayerState {

  public:
    /**
    * @brief constructor
    * @param p reference to player for sm context
    */
    explicit Sliding(Player &p);

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
    /**
     * @brief process input
     */
    virtual void handle_input() override;

    /// slide direction
    GameLib::Vector3 dir;

    /// to track distance
    GameLib::Vector3 start;

    /// some time at the end to get up
    bool getting_up = false;

    /// time the get up time
    int down_frames = 0;
};

} // SenselessSoccer
