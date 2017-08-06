#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

class Head : public Locomotion {
  public:
    Head(Player *p);
    virtual void OnStart();
    virtual void OnStep(const float dt);
    virtual void OnEnd();
    virtual bool StateOver();
    virtual void ChangeToNextState();
    virtual void Modify(Modifier mod) override;

    void Init(GameLib::Vector3 dir);

  protected:
    GameLib::Vector3 direction;
};

} // namespace Senselesssoccer
