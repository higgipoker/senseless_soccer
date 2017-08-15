#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

/**
 * @brief player runs in a specific direction until state is stopped
 */
class Head : public Locomotion {
public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player for state machine context
     */
    Head(Player *p);

    /**
     * @brief state start
     */
    virtual void OnStart() override;

    /**
     * @brief state step
     * @param [in] dt time delta
     */
    virtual void OnStep(const float dt) override;

    /**
     * @brief state end
     */
    virtual void OnEnd() override;

    /**
     * @brief check for end condition
     */
    virtual bool StateOver() override;

    /**
     * @brief init the state
     * @param [in] dir direction
     */
    void Init(GameLib::Vector3 dir);

    /**
     * @brief some states can be ended manually
     */
    virtual void Cancel() override;

protected:
    GameLib::Vector3 direction;
};

} // namespace Senselesssoccer
