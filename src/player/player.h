/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file player.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "../ball/ball.h"
#include "../graphics/player_sprite.h"
#include "../joysticker/controller.h"
#include "../pitch/pitch.h"
#include "../team/roles/role.h"
#include "brain/brain.h"

namespace SenselessSoccer {

class Team;

/** @brief class to represent a player entity */
class Player : public GameLib::StateMachine,
               public GameLib::GameEntity,
               public ControllerListener {
  public:
    /**
     * @brief constructor
     */
    explicit Player(GameLib::Physical *p, GameLib::Renderable *r);

    /**
     *@brief derived entities can do their own extra handling
     *@param dt time delta
     */
    virtual void Update(float dt) override;

    /**
     * @brief connect an input
     * @param i pointer to input device (can be null)
     */
    void AttachInput(Controller *i);

    /**
     * @brief detatch an input
     */
    void DetatchInput();

    /**
     * @brief handle a controller event
     * @param event an event to handle
     */
    virtual void OnControllerEvent(ControllerEvent event) override;

    /**
     * @brief rpc call for player
     * @param params list of params
     */
    virtual void Call(std::vector<std::string> params) override;

    /// players team
    Team *my_team;

    /// opposing team
    Team *other_team;

    /// a player can have a playing role (eg right back)
    Role *role;

    /// track distance from ball
    float distance_from_ball = 0;

    /// track if i have the ball
    bool in_possession = false;

    /// convenient access to match stuff
    static Ball *ball;
    static Pitch *pitch;

  protected:
    /// to save casting generic sprite to player sprite
    PlayerSprite *player_sprite;

    /// input controller
    Controller *input;

    /// a brain
    Brain brain;

    /// how fast can the player run
    const unsigned int DEFAULT_SPEED = 200;
    unsigned int running_speed = DEFAULT_SPEED;

    /// to collide with the ball for dribbling
    GameLib::Circle dribble_circle;

    /// for close control
    GameLib::Circle close_control_circle;

    /// track change direction, so we donthave to calc it multiple times in a
    /// frame
    bool changed_direction;

    /// until we think of a better way to transition to slide tackle state
    bool sliding = false;

    /// for calcing change direction
    GameLib::Vector3 last_direction;

    /**
     * @brief helper to update player position
     * @param dt time delta
     */
    void update_position(float dt);

    /**
     * @brief helper to normalize the velocity
     */
    void normalize_velocity();

    /**
     * @brief helper to set the sprite animation
     */
    void animate();

    /**
     * @brief player gained possession
     */
    void gained_possession();

    /**
     * @brief player lost possession
     */
    void lost_possession();

    /**
     * @brief dribble circle must be updated every frame depending on players
     * current position
     */
    void update_dribble_circle();

    /**
     * @brief push the ball forward
     * @param direction dribbling direction
     */
    void do_dribble(const GameLib::Vector3 &direction);

    /**
     * @brief push the ball forward
     * @param direction sliding direction
     */
    void do_slide_tackle(const GameLib::Vector3 &direction);

    /**
     * @brief close control mechanism
     */
    void do_close_control();

    /**
     * @brief test if ball is under control
     */
    bool ball_under_control();

    /**
     * @brief do a short pass
     * @param recipient recieving player
     */
    void short_pass();

    /**
     * @brief shoot!!
     */
    void shoot();

    /**
     * @brief clear the ball
     */
    void clearance();

    /**
     * @brief do a sliding tackle
     */
    void slide_tackle();

    /**
     * @brief kick the ball
     * @param force force to kick ball with
     */
    void kick(float force);

    /**
     * @brief calc pass range triangle
     */
    void calc_pass_recipients();

    /**
     * @brief helper
     * @return
     */
    float distance_to_goal();

  public:
    // ------------------------------------------------------------
    // state machine pattern friends
    // ------------------------------------------------------------
    friend class PlayerState;
    friend class Standing;
    friend class Running;
    friend class Sliding;
    friend class Brain;
    friend class BrainState;
    friend class BrainIdle;
    friend class BrainDribble;
    friend class BrainCover;
    friend class BrainSupport;
    friend class BrainPass;
    friend class BrainReceive;
    friend class BrainGetBall;
    friend class BrainShoot;
    friend class BrainPress;
    friend class BrainClear;
};

} // SenselessSoccer
