#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

class Arrive : public Locomotion {

  public:
    Arrive(Player *p);

    virtual void OnStart() override;
    virtual void OnStep(const float dt) override;
    virtual void OnEnd() override;
    virtual bool StateOver() override;
    virtual void ChangeToNextState() override;
    void Init(GameLib::Vector3 target);
    virtual void Modify(Modifier mod) override;

  protected:
    GameLib::Vector3 last_distance;
};

} // namespace Senselesssoccer
