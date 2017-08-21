
#pragma once

#include <gamelib/input/input.h>

#include "../ball/ball.h"
#include "../graphics/player_sprite.h"
#include "../pitch/pitch.h"
#include "../team/roles/role.h"
#include "brain/brain.h"

namespace SenselessSoccer {

class Team;

/** @brief class to represent a player entity */
class Player : public GameLib::StateMachine, public GameLib::GameEntity {
public:
    /**
     * @brief constructor
     */
    Player(GameLib::Physical *p);

    /**
     *@brief derived entities can do their own extra handling
     *@param dt time delta
     */
    virtual void Update(float dt) override;

    /**
     * @brief connect the player sprite
     * @param sprite reference to a sprite to use
     * @param shadow reference to shadow sprite
     */
    void ConnectSprite(PlayerSprite &sprite, PlayerSprite &shadow);

    /**
     * @brief connect an input
     * @param i pointer to input device (can be null)
     */
    void AttachInput(GameLib::Input *i);

    /**
     * @brief detatch an input
     */
    void DetatchInput();

    /**
     * @brief player gained possession
     */
    void OnGainedPossession();

    /**
     * @brief player lost possession
     */
    void OnLostPossession();

    /**
     * @brief do a short pass
     * @param recipient recieving player
     */
    void ShortPass(Player *recipient);

    /**
     * @brief shoot!!
     */
    void Shoot();

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
    int distance_from_ball;

    /// track if i have the ball
    bool in_possession;

    /// convenient access to match stuff
    static Ball *ball;
    static Pitch *pitch;

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

    /// track change direction, so we donthave to calc it multiple times in a
    /// frame
    bool changed_direction;

    /// for calcing change direction
    GameLib::Vector3 last_direction;

    /**
     * @brief process input
     */
    void handle_input();

    /**
     * @brief helper to update player position
     * @param dt time delta
     */
    void update_position(float dt);
    GameLib::Vector3 project_position(float dt);

    /**
     * @brief helper to normalize the velocity
     */
    void normalize_velocity();

    /**
     * @brief helper to set the sprite animation
     */
    void animate();

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
     * @brief close control mechanism
     */
    void do_close_control();

    /**
     * @brief test if ball is under control
     */
    bool ball_under_control();

    /**
     * \breif kick the ball
     * @param force force to kick ball with
     */
    void kick(float force);

    /**
     * @brief calc pass range triangle
     */
    void calc_pass_recipients();

    bool suspend_ball_interaction = false;

    /// helper
    int distance_to_goal(){
        GameLib::Vector3 goal_center(pitch->metrics.north_goal.x1, pitch->metrics.north_goal.y1);
        goal_center.x += (pitch->metrics.north_goal.x2 - pitch->metrics.north_goal.x1) / 2;

        return (physical->position - goal_center).magnitude();

    }

    /// debug


public:
    // ------------------------------------------------------------
    // state machine pattern friends
    // ------------------------------------------------------------
    friend class Standing;
    friend class Running;
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
};

} // SenselessSoccer
