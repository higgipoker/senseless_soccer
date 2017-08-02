#pragma once

#include "locomotion.h"

namespace SenselessSoccer {

class Cover : public Locomotion {
 public:
  Cover(Player *p);
  virtual void OnStart();
  virtual void OnStep(const float dt);
  virtual void OnEnd();
  virtual bool StateOver();
  virtual void ChangeToNextState();

 protected:
  int last_ball_sector;
  int last_target_sector;
};

}  // namespace Senselesssoccer
