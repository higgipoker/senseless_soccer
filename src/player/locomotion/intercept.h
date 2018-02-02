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
class Intercept : public Locomotion {
public:
    /**
     *@brief constructor
     */
    explicit Intercept(Player *p);

    /**
     *@brief state start
     */
    virtual void OnStart();

    /**
     *@brief state step
     */
    virtual void OnStep(const double dt);

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
    void Init(GameLib::Physical *_evader);

    /**
     * @brief some states can be ended manually
     */
    virtual void Cancel() override;

protected:

    /// object to intercept
    GameLib::Physical *evader;

    /// helper to track progress
    GameLib::Vector3 last_distance;

    /**
     * @brief helper to seek
     */
    void seek(GameLib::Vector3 _target);
};
}

