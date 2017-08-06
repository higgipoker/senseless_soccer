#pragma once
#include "../player.h"
#include <gamelib/statemachine/state.h>

namespace SenselessSoccer {
class BrainState : public GameLib::State {
  public:
    BrainState(Player *p);
    virtual void OnStart() override;
    virtual void OnStep(const float _dt) override;
    virtual void OnEnd() override;
    virtual bool StateOver() override;
    virtual void ChangeToNextState() override;

  protected:
    Player *player;
};
}
