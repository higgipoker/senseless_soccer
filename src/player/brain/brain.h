#pragma once

#include "../locomotion/locomotion_manager.h"
#include <gamelib/statemachine/state_machine.h>

namespace SenselessSoccer {

/** \brief all possible brainstates */
enum brainstate { BRAINSTATE_NONE, BRAIN_COVER, BRAIN_DRIBBLE, BRAIN_GETBALL, BRAIN_IDLE, BRAIN_SUPPORT };

/** \brief all possible modifier types */
enum modifier { MODIFIER_NONE, COVER_PRESS, COVER_PRESS_HIGH, COVER_SHADOW, COVER_SHADOW_DEEP, SUPPORT_PASS, SUPPORT_BACKUP, SUPPORT_RUN };

class Player;
class Brain : public GameLib::StateMachine {
  public:
    /**
     * @brief Brain
     * @param p
     */
    Brain(Player *p);

    /**
     * @brief Step
     * @param dt
     */
    void Step(float dt);

    /**
     * @brief locomotion
     */
    LocomotionManager locomotion;

    /**
      \brief activate a brain state manually
      */
    void ActivateState(brainstate bs);

    /**
      \brief set a locomotion modifier
      \param [in] m modifier type
    */
    void SetModifier(const modifier m);

  protected:
    Player *player;
    bool in_pitch(float dt);

  public:
    friend class BrainDribble;
};

} // namespace SenselessSoccer
