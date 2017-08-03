#pragma once

#include "locomotion.h"
#include <gamelib/physics/physical.h>

namespace SenselessSoccer {

/** \brief "chase after" behaviour
  */
class Pursue : public Locomotion {
  public:
    Pursue(Player *p);

    virtual void OnStart();
    virtual void OnStep(const float dt);
    virtual void OnEnd();
    virtual bool StateOver();
    virtual void ChangeToNextState();
    virtual void Modify(Modifier mod) override;

    void Init(GameLib::Physical *t);

  protected:
    GameLib::Physical *target;
    GameLib::Vector3 last_distance;
};
}
