#pragma once
#include "../../player.h"
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

    /**
     * \brief modify the state parameters on the fly
     */
    virtual void Modify(modifier mod);

  protected:
    Player *player;

    /// state paramaters modifier
    std::vector<modifier> modifiers;
};
}
