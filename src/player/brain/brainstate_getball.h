#pragma once

#include "../player.h"
#include "brainstate.h"

namespace SenselessSoccer {

/*
 * ai state to make plyer go get a loose ball
 */
class BrainGetBall : public BrainState {
  public:
    BrainGetBall(Player *player);

    virtual void OnStart() override;
    virtual void OnStep(const float _dt) override;
    virtual void OnEnd() override;
    virtual bool StateOver() override;
    virtual void ChangeToNextState() override;

  protected:
};
}
