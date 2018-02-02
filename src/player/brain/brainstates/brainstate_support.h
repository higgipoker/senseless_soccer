/**
 * \file 	src/player/locomotion/Support.h
 * \author 	Paul Higgins
 * \date 	14.08.2017
 * @brief 	Support type locomotion
 *
 * Description
 *
 *
 */
#pragma once

#include "brainstate.h"

namespace SenselessSoccer {

/**
 * @brief this the equavelnt of the Cover locomotion for attacking
 *          this one can be modified as follows:
 *          pass - try to get into a position to receive a pass from the ball carrier
 *          backup - hold position to cover a forward running player
 *          run - make a forward run to make an option for through ball or long ball
 */
class BrainSupport : public BrainState {
public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player for state machine context
     */
    explicit BrainSupport(Player *p);

    /**
     * @brief state on start
     */
    virtual void OnStart() override;

    /**
     * @brief state on step
     * @param [in] dt time delta
     */
    virtual void OnStep(const double dt) override;

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

    /**
      @brief modify the state to backup (cover for) other players
      */
    int mod_for_backup(int sector);

    /**
      @brief modify the state to try to get to a position to receive a pass
      */
    void mod_for_pass();
};

} // namespace Senselesssoccer
