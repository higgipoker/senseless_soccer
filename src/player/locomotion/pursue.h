/**
 * \file 	src/player/locomotion/pursue.h
 * \author 	Paul Higgins
 * \date 	14.08.2017
 * @brief 	cover type locomotion
 *
 * Description
 *
 *
 */
#pragma once

#include "locomotion.h"
#include <gamelib/physics/physical.h>

namespace SenselessSoccer {

/**
 * @brief player follows a specified target
 */
class Pursue : public Locomotion {
public:
    /**
     *@brief constructor
     */
    explicit Pursue(Player *p);

    /**
     *@brief state start
     */
    virtual void OnStart();

    /**
     *@brief state step
     */
    virtual void OnStep(const float dt);

    /**
     *@brief state end
     */
    virtual void OnEnd();

    /**
     *@brief check for state over condition
     */
    virtual bool StateOver();

    /**
     *@brief Init
     */
    void Init(GameLib::Physical *t);

    /**
     * @brief some states can be ended manually
     */
    virtual void Cancel() override;

protected:
    /// target to follow
    GameLib::Physical *target;

    /// track last distance
    GameLib::Vector3 last_distance;
};
}
