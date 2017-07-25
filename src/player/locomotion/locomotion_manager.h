#pragma once

#include <queue>
#include <gamelib/statemachine/state_machine.h>
#include <gamelib/physics/physical.h>
#include <gamelib/physics/physical.h>
#include "arrive.h"
#include "pursue.h"

namespace SenselessSoccer{

class LocomotionManager : public GameLib::StateMachine {
 public:
  /**
   * \brief constructor
   */
  LocomotionManager(GameLib::Physical *physical);

  /**
   * \brief destruct
   */
  ~LocomotionManager();

  /**
  * \brief polling to update current locomtion
  * \param dt time delta
  */
  void UpdateLocomotion(float dt);

  /**
   * \brief activate a new locomotion
   * \param l pointer to new locomotion
   */
  void SetLocomotion(Locomotion *l);

  /**
   * \brief turn on arrive behavior
   * \param dest destination
   */
  void ActivateArrive(GameLib::Vector3 dest);

  /**
   * \brief turn on pursue behavior
   * \param follow entity to ppursue
   */
  void ActivatePursue(GameLib::Physical *follow);

  /**
   * \brief cancel
   */
  void Cancel(void);

 private:
  /// sm context
  GameLib::Physical *player;

  /// point to currently active behavoiur
  Locomotion *behaviour;

  /// an arrive behaviour
  Arrive *arrive;

  /// a pursue behaviour
  Pursue *pursue;

  /// a queue of locomotion orders
  std::queue<Locomotion*> behaviour_queue;

  /**
  * @brief changeLocomotion (locomotion)
  */
  void change_locomotion(Locomotion *b);
};

}// namespace SenselessSoccer
