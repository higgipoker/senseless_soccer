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

//   /**
//    * @brief turnOnWandering
//    */
//   void TurnOnWandering(GameLib::Rectangle bounds);
//
//   /**
//    * @brief turnOffWandering
//    */
//   void turnOffWandering();
//
//   /**
//    * @brief turnOnSeeking
//    */
//   void turnOnSeeking(GameLib::Vector3 d);
//
//   /**
//    * @brief turnOffSeeking
//    */
//   void turnOffSeeking();
//
//   /**
//    * @brief turnOnSeeking
//    */
//   void turnOnHeading(GameLib::Vector3 d);
//
//   /**
//    * @brief turnOffSeeking
//    */
//   void turnOffHeading();
//
//   /**
//    * @brief turnOnPursuit
//    */
//   void turnOnPursuit(GameLib::PhysicalObject *t);
//
//   /**
//    * @brief turnOffPursuit
//    */
//   void turnOffPursuit();
//
//   /**
//    * @brief turnOnIntercept
//    */
//   void turnOnIntercept(GameLib::PhysicalObject *t);
//
//   /**
//    * @brief turnOffIntercept
//    */
//   void turnOffIntercept();
//
//   /**
//    * @brief turnOnGoaltend
//    */
//   void turnOnGoaltend(GameLib::PhysicalObject *defending_goal);
//
//   /**
//    * @brief turnOffGoaltend
//    */
//   void turnOffGoaltend();
//
//   /**
//    * @brief turnOnCovering
//    */
//   void turnOnCovering();
//
//   /**
//    * @brief turnOffCovering
//    */
//   void turnOffCovering();
//
//   /**
//    * @brief turnOnWaiting
//    */
//   void turnOnWaiting();
//
//   /**
//    * @brief turnOffWaiting
//    */
//   void turnOffWaiting();
//
//   /**
//    * @brief turnOnJump
//    */
//   void turnOnJump();
//
//   /**
//    * @brief turnOffJump
//    */
//   void turnOffJump();
//
//   /**
//    * @brief turnOnJump
//    */
//   void turnOnDive(const GameLib::Point &_interesect);
//
//   /**
//    * @brief turnOffJump
//    */
//   void turnOffDive();

  /**
   * \brief cancel
   */
  void Cancel(void);

 private:
  //. sm context
  GameLib::Physical *player;

  /// point to currently active behavoiur
  Locomotion *behaviour;

  /// an arrive behaviour
  Arrive *arrive;

  /// a pursue behaviour
  Pursue *pursue;

//   /// cover behaviour
//   Cover *behaviour_cover;
//
//   /// seek behaviour
//   Seek *behaviour_seek;
//
//   /// heading behaviour
//   Heading *behaviour_heading;
//
//   /// pursue behaviour
//   Pursue *behaviour_pursue;
//
//   /// interpose behaviour
//   Interpose *behaviour_interpose;
//
//   /// interpose behaviour
//   Intercept *behaviour_intercept;
//
//   /// goaltend behaviour
//   Goaltend *behaviour_goaltend;
//
//   /// jump behaviour
//   Jump *behaviour_jump;
//
//   /// dive behaviour
//   Dive *behaviour_dive;

  /// a queue of locomotion orders
  std::queue<Locomotion*> behaviour_queue;

  /**
  * @brief changeLocomotion (locomotion)
  */
  void change_locomotion(Locomotion *b);
};

}// namespace SenselessSoccer
