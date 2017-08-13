/**
 * \file 	src/player/locomotion/locomption.h
 * \author 	Paul Higgins
 * \date 	14.08.2017
 * \brief 	base locomotion
 *
 * Description
 *
 *
 */
#pragma once

#include <gamelib/math/vector3.h>
#include <string>
#include <vector>

namespace SenselessSoccer {

/// forward declaration
class Player;

/**
 * \brief base class for locomotion
 */
class Locomotion {
  public:
    /**
     * \brief constructor
     * \param [in] p pointer back to player
     */
    Locomotion(Player *p);

    /**
     * \brief on state start
     */
    virtual void OnStart() = 0;

    /**
     * \brief on state step
     */
    virtual void OnStep(const float _dt) = 0;

    /**
     * \brief on state end
     */
    virtual void OnEnd() = 0;

    /**
     * \brief check if state end condition is met
     */
    virtual bool StateOver() = 0;

  protected:
    /// pointer back to player for state machine pattern
    Player *player;

    /// track if end condition is met
    bool state_over;

    /// track destination
    GameLib::Vector3 destination;

    /// hast he destination been reached?
    bool destination_reached;
};

} // namespace SenselessSoccer
