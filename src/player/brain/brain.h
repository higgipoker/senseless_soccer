#pragma once

#include "../locomotion/locomotion_manager.h"
#include <gamelib/statemachine/state_machine.h>

namespace SenselessSoccer {

/** @brief all possible brainstates */
enum brainstate {
    BRAIN_NONE,
    BRAIN_COVER,
    BRAIN_DRIBBLE,
    BRAIN_GETBALL,
    BRAIN_IDLE,
    BRAIN_SUPPORT,
    BRAIN_PASS,
    BRAIN_RECEIVE,
    BRAIN_SHOOT,
    BRAIN_PRESS,
    BRAIN_CLEAR
};

/** @brief all possible modifier types */
enum modifier {
    MODIFIER_NONE,
    COVER_PRESS,
    COVER_PRESS_HIGH,
    COVER_SHADOW,
    COVER_SHADOW_DEEP,
    SUPPORT_PASS,
    SUPPORT_BACKUP,
    SUPPORT_RUN,
    DRIBBLE_CHANGE_DIRECTION,
};

class Player;
class Brain : public GameLib::StateMachine {
public:
    /**
     * @brief Brain
     * @param p pointer back to player
     */
    explicit Brain (Player *p);

    /**
     * @brief Step
     * @param dt time delta
     */
    void Step (float dt);

    /**
      * @brief activate a brain state manually
      */
    void ActivateState (brainstate bs);

    /**
      * @brief set a locomotion modifier
      * @param [in] m modifier type
      */
    void SetModifier (const modifier m);

    /// locomotio manager
    LocomotionManager locomotion;

    /// a debug string
    std::string statename;

protected:
    /// pointer back to player for sm context
    Player *player;

    /// is the playe rin the pitch
    bool in_pitch (float dt);

public:
    friend class BrainDribble;
};

} // namespace SenselessSoccer
