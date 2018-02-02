/**
 * \file 	src/player/locomotion/arrive.h
 * \author 	Paul Higgins
 * \date 	14.08.2017
 * @brief 	arrive type locomotion
 *
 * Description
 *
 *
 */
#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

/**
 * @brief Like a "goto" instruction
 *          the player simply runs to the specified destination
 *          and then stops.
 */
class Arrive : public Locomotion {

public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player
     */
    explicit Arrive(Player *p);

    /**
     * @brief state on start
     */
    virtual void OnStart() override;

    /**
     * @brief state on step
     */
    virtual void OnStep(const double dt) override;

    /**
     * @brief state on end
     */
    virtual void OnEnd() override;

    /**
     * @brief state check if finished
     */
    virtual bool StateOver() override;

    /**
     * @brief init the state
     */
    void Init(GameLib::Vector3 target);

    /**
     * @brief some states can be ended manually
     */
    virtual void Cancel() override;

protected:
    /// tracks last distance from target destination
    GameLib::Vector3 last_distance;
};

} // namespace Senselesssoccer
