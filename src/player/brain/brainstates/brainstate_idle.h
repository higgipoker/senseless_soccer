#pragma once

#include "../../player.h"
#include "brainstate.h"

namespace SenselessSoccer {

class BrainIdle : public BrainState {
  public:
    BrainIdle(Player *player);

    virtual void OnStart() override;
    virtual void OnStep(const float _dt) override;
    virtual void OnEnd() override;
    virtual bool StateOver() override;
    virtual void ChangeToNextState() override;

  protected:
};
}
