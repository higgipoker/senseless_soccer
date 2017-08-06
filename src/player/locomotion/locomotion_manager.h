#pragma once

#include "arrive.h"
#include "cover.h"
#include "head.h"
#include "pursue.h"
#include <gamelib/statemachine/state_machine.h>
#include <queue>

namespace SenselessSoccer {

enum behaviours { ARRIVE, COVER, HEAD, PURSUE };

class Player;
class LocomotionManager : public GameLib::StateMachine {
  public:
    LocomotionManager(Player *p);
    ~LocomotionManager();

    void UpdateLocomotion(float dt);
    void SetLocomotion(Locomotion *l);
    void ActivateArrive(GameLib::Vector3 dest);
    void ActivatePursue(GameLib::Physical *follow);
    void ActivateHead(GameLib::Vector3 dir);
    void ActivateCover();
    void Cancel(void);

  private:
    Player *player;
    Locomotion *behaviour;
    Arrive *arrive;
    Pursue *pursue;
    Cover *cover;
    Head *head;
    std::queue<Locomotion *> behaviour_queue;
    void change_locomotion(Locomotion *b);
};

} // namespace SenselessSoccer
