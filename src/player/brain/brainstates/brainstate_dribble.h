#pragma once
#include "brainstate.h"
#include <gamelib/utils/timer.h>
namespace SenselessSoccer {

class BrainDribble : public BrainState {
  public:
    BrainDribble(Player *p);

    virtual void OnStart() override;
    virtual void OnStep(const float _dt) override;
    virtual void OnEnd() override;
    virtual bool StateOver() override;
    virtual void ChangeToNextState() override;

  protected:
    void change_direction();
    GameLib::Timer timer;
};
}

/*
 * The point of the dribble state is to run (physical ball dribbling happens automatically) to a specified location, whilst
 * avoiding obstacles (other players)
 *
 * probable targets are:
 * - dribble to safety (eg defender)
 * - dribble to wing (eg winger looking for a cross)
 * - dribble to goal (eg midfielder looking for a through ball or striker looking for a shoot
 *
 * there are only 2 possible obstacles:
 * - player
 * - pitch boundary
 *
 * there are a few possible stop conditions:
 * - reached destination
 * - ran into a dangerous position or situation (context sensetive)
 * - lost ball
 * - alternative excellent option becomes available
 */
