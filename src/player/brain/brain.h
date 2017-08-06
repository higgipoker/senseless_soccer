#pragma once

#include "../locomotion/locomotion_manager.h"
#include <gamelib/statemachine/state_machine.h>

namespace SenselessSoccer {
class Player;
class Brain : public GameLib::StateMachine {
  public:
    Brain(Player *p);
    void Step(float dt);
    LocomotionManager locomotion;

  protected:
    Player *player;
    bool in_pitch(float dt);

  public:
    friend class BrainDribble;
};

} // namespace SenselessSoccer
