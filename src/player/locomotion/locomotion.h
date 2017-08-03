#pragma once

#include <gamelib/math/vector3.h>
#include <gamelib/statemachine/state.h>
#include <string>

namespace SenselessSoccer {

enum Modifier { NONE, COVER_PRESS, COVER_SHADOW };

class Player;
class Locomotion : public GameLib::State {
  public:
    Locomotion(Player *p);
    virtual ~Locomotion();

    virtual void OnStart() = 0;
    virtual void OnStep(const float _dt) = 0;
    virtual void OnEnd() = 0;
    virtual bool StateOver() = 0;
    virtual void ChangeToNextState() = 0;
    virtual void Modify(Modifier mod) = 0;

  protected:
    Player *player;
    bool state_over;
    GameLib::Vector3 destination;
    bool destination_reached;
    Modifier modifier;
};
} // namespace SenselessSoccer
