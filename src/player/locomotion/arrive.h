#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

class Arrive : public Locomotion {

  public:
    Arrive(Player *p);

    virtual void OnStart();
    virtual void OnStep(const float dt);
    virtual void OnEnd();
    virtual bool StateOver();
    virtual void ChangeToNextState();
    void Init(GameLib::Vector3 target);
    virtual void Modify(Modifier mod) override;

  protected:
    GameLib::Vector3 last_distance;
};

} // namespace Senselesssoccer
