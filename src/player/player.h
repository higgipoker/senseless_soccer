/*
 * player.h
 *
 *  Created on: Jun 10, 2017
 *      Author: higgi
 */
#pragma once

#include <gamelib/gamelib.h>

#include "../graphics/player_sprite.h"
#include "../ball/ball.h"
#include "brain/brain.h"

namespace SenselessSoccer {

/** \brief class to represent a player entity */
class Player : 	public GameLib::StateMachine, public GameLib::GameEntity {
public:

    /**
     * \brief constructor
     */
    Player();

	/**
     * \brief derived entities can do their own extra handling
     * \param dt time delta
     */
    virtual void Update( float dt ) override;

    /**
     * \brief connect the player sprite
     * \param sprite reference to a sprite to use
	 * \param shadow reference to shadow sprite
     */
    void ConnectSprite(PlayerSprite &sprite, PlayerSprite &shadow);

    /**
     * \brief connect an input
     * \param i pointer to input device (can be null)
     */
    void AttachInput(GameLib::Input *i);

    /**
     * \brief detatch an input
     */
    void DetatchInput();

	/**
	 * \brief manually set behaviour
	 */
	void SetBehaviour(const std::string &new_behaviour, std::vector<std::string> params);
    void SetBehaviour(const std::string &new_behaviour, GameLib::GameEntity *e);

	virtual void Call(std::vector<std::string> params) override;

    /// convenient access to the ball
    static Ball *ball;

protected:

    /// to access the sprite specific functionality of renderable (eg animate)
    PlayerSprite *player_sprite;

    /// input controller
    GameLib::Input *input;

	/// a brain
	Brain brain;

    /// how fast can the player run
    unsigned int running_speed;

    /// to collide with the ball for dribbling
    GameLib::Circle dribble_circle;

	/// for close control
	GameLib::Circle close_control_circle;

	/// track change direction, so we donthave to calc it multiple times in a frame
	bool changed_direction;

	/// for calcing change direction
	GameLib::Vector3 last_direction;

    /**
     * \brief process input
     */
    void handle_input();

    /**
     * \brief helper to update player position
     * \param dt time delta
     */
    void update_position(float dt);

    /**
     * \brief helper to normalize the velocity
     */
    void normalize_velocity();

    /**
     * \brief helper to set the sprite animation
     */
    void animate();

    /**
     * \brief dribble circle must be updated every frame depending on players current position
     */
    void update_dribble_circle();

	/**
	 * \brief push the ball forward
	 * \param direction dribbling direction
	 */
	void do_dribble( const GameLib::Vector3 &direction );

	/**
	 * \brief close control mechanism
	 */
	void do_close_control();

	/**
	 * \brief test if ball is under control
	 */
	bool ball_under_control();

	/**
	 * \breif kick the ball
	 * \param force force to kick ball with
	 */
	void kick(float force);

public:
    // ------------------------------------------------------------
    // state machine pattern friends
    // ------------------------------------------------------------
    friend class Standing;
    friend class Running;
};

}// SenselessSoccer
