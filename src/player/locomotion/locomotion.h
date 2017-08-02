#pragma once

#include <gamelib/statemachine/state.h>
#include <gamelib/math/vector3.h>
#include <string>

namespace SenselessSoccer {

/* declare the player class */
class Player;

/**
 --------------------------------------------------

 @brief Movement behaviour base class

 --------------------------------------------------
 */
class Locomotion : public GameLib::State {
 public:
  /**
   * @brief constructor
   * @param physical pointer back to sm context
   */
  Locomotion(Player *p);

  /**
   * @brief destructor
   */
  virtual ~Locomotion();

  /**
 * \brief onStart
 */
  virtual void OnStart() = 0;

  /**
   * \brief onStep
   * \param _dt time delta
   */
  virtual void OnStep(const float _dt) = 0;

  /**
   * \brief onEnd
   */
  virtual void OnEnd() = 0;

  /**
   * \brief stateOver
   */
  virtual bool StateOver() = 0;

  /**
   * \brief changeToNextState
   */
  virtual void ChangeToNextState() = 0;

 protected:
  /// pointer back to player
  Player *player;

  /// tracking
  bool state_over;

  /// track destination
  GameLib::Vector3 destination;
  bool destination_reached;
};
}  // namespace SenselessSoccer
