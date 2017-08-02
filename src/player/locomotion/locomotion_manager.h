#pragma once

#include <queue>
#include <gamelib/statemachine/state_machine.h>
#include "arrive.h"
#include "pursue.h"
#include "cover.h"

namespace SenselessSoccer{

class Player;
class LocomotionManager : public GameLib::StateMachine {
 public:

  LocomotionManager(Player *p);
  ~LocomotionManager();

  void UpdateLocomotion(float dt);
  void SetLocomotion(Locomotion *l);
  void ActivateArrive(GameLib::Vector3 dest);
  void ActivatePursue(GameLib::Physical *follow);
  void ActivateCover();
  void Cancel(void);

 private:
  Player *player;
  Locomotion *behaviour;
  Arrive *arrive;
  Pursue *pursue;
  Cover *cover;
  std::queue<Locomotion*> behaviour_queue;
  void change_locomotion(Locomotion *b);
};

}// namespace SenselessSoccer
