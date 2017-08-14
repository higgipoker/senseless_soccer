/**
 * \file 	src/player/locomotion/BrainCover.h
 * \author 	Paul Higgins
 * \date 	14.08.2017
 * @brief 	BrainCover type locomotion
 *
 * Description
 *
 *
 */
#pragma once

#include "brainstate.h"

namespace SenselessSoccer {

/**
 * @brief more complex kind of locomotion - the player goes
 *          to a pitch sector depending on the current ball sector.
 *          Locations defined by tactics/role file
 *
 *          Can be passed a modifier to push futher forward or
 *          drop deeper.
 */
class BrainCover : public BrainState {
  public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player for state machine context
     */
    BrainCover(Player *p);

    /**
     * @brief state on start
     */
    virtual void OnStart() override;

    /**
     * @brief state on step
     * @param [in] dt time delta
     */
    virtual void OnStep(const float dt) override;

    /**
     * @brief state on end
     */
    virtual void OnEnd() override;

    /**
     * @brief check if end condition met
     */
    virtual bool StateOver() override;

    /**
     * @brief modify the state parameters on the fly
     */
    virtual void Modify(modifier mod) override;

  protected:
    /// track last ball sector
    int last_ball_sector;

    /// track last target sector
    int last_target_sector;
};

} // namespace Senselesssoccer
