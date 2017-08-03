/*
 * player.cpp
 *
 *  Created on: Jun 10, 2017
 *      Author: higgi
 */
#include "player.h"

#include "../game/game.h"
#include "locomotion/arrive.h"
#include "locomotion/pursue.h"
#include "player_states/standing.h"

namespace SenselessSoccer {

Ball *Player::ball = nullptr;
Pitch *Player::pitch = nullptr;

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Player::Player(GameLib::Physical *p)
    : GameLib::GameEntity(p),

      // sprite will be attached later
      player_sprite(nullptr),

      // no connected input
      input(nullptr),

      /// a brain
      brain(this),

      // how fast the player moves
      running_speed(3000),

      // tracker
      changed_direction(false) {
    name = "player";

    // set up an inital state
    InitState(new Standing(*this));

    // players sprite feet at physical location
    anchor_type = GameLib::ANCHOR_BASELINE;

    // dribble circle size
    dribble_circle.radius = 4;

    // close control circle
    close_control_circle.radius = 8;
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Player::Update(float dt) {
    GameLib::GameEntity::Update(dt);

    // advance state machine
    GameLib::StateMachine::Step(dt);

    // hz order
    renderable->z_order = physical->position.y;

    // only if input is attached
    if (input) {
        physical->ResetVelocity();
        handle_input();
    } else {
        brain.Step(dt);
    }

    // update the player position
    update_position(dt);

    // update the sprite animation
    animate();

    // update dribble circle
    update_dribble_circle();

    // check for collision with ball (dribble)
    if (GameLib::CollisionDetector::collision(dribble_circle, ball->GetCollidable())) {
        do_dribble(physical->velocity.normalised());
    }

    // calc if changed direction
    if (last_direction.equals(physical->velocity.getNormalizedToUnits())) {
        changed_direction = false;
    } else {
        changed_direction = true;
    }

    // save direction
    last_direction = physical->velocity.getNormalizedToUnits();

    // ball control
    if (changed_direction && ball_under_control() && physical->velocity.magnitude()) {
        do_close_control();
    }
}

// ------------------------------------------------------------
// ConnectSprite
// ------------------------------------------------------------
void Player::ConnectSprite(PlayerSprite &sprite, PlayerSprite &shadow) {
    // the base class renderable object
    renderable = &sprite;

    // and shadow
    renderable->shadow = &shadow;

    // the derived type (for convenience to save casting)
    player_sprite = &sprite;
}

// ------------------------------------------------------------
// AttachInput
// ------------------------------------------------------------
void Player::AttachInput(GameLib::Input *i) {
    input = i;
}

// ------------------------------------------------------------
// DetatchInput
// ------------------------------------------------------------
void Player::DetatchInput() {
    // null means no input attached to this player
    input = nullptr;
}

// ------------------------------------------------------------
// handle_input
// ------------------------------------------------------------
void Player::handle_input() {
    // poll for inputs
    input->Update();

    // up
    if (input->event_states[GameLib::UP]) {
        physical->velocity.y = -1;
    }

    // down
    if (input->event_states[GameLib::DOWN]) {
        physical->velocity.y = 1;
    }

    // left
    if (input->event_states[GameLib::LEFT]) {
        physical->velocity.x = -1;
    }

    // right
    if (input->event_states[GameLib::RIGHT]) {
        physical->velocity.x = 1;
    }

    // fire released
    if (input->event_states[GameLib::FIRE_UP]) {
        if (ball_under_control()) {
            kick(input->event_states[GameLib::FIRE_LENGTH_CACHED] * 25);
        }
    }
}

// ------------------------------------------------------------
// update_position
// ------------------------------------------------------------
void Player::update_position(float dt) {
    // normalises velocity for consistent speed in diagonals
    normalize_velocity();

    // update position according to velocity and individual running speed
    physical->position += physical->velocity * dt * running_speed;
}

// ------------------------------------------------------------
// normalize_velocity
// ------------------------------------------------------------
void Player::normalize_velocity() {
    // normalises to units
    physical->velocity.normalise();

    // normalizes for diagonals
    float mag = physical->velocity.magnitude();
    if (mag > running_speed) {
        physical->velocity *= running_speed;
    }
}

// ------------------------------------------------------------
// animate
// ------------------------------------------------------------
void Player::animate() {
    // get the angle to the ball
    GameLib::Vector3 to_ball = ball->physical->position - physical->position;

    // to nearest 45 degrees
    to_ball = to_ball.roundAngle(45);
    float angle_to_ball = to_ball.angle();

    // set the animation based on velocity (running direction)
    player_sprite->UpdateAnimation(physical->velocity, angle_to_ball);

    // poll animation
    player_sprite->Animate();

    // update shadow
    player_sprite->shadow->SetPosition(player_sprite->GetPosition().x + 3, /* TODO magic numbers here for shadow offset */
                                       player_sprite->GetPosition().y + 7);
}

// ------------------------------------------------------------
// update_dribble_circle
// ------------------------------------------------------------
void Player::update_dribble_circle() {
    // set dribble circle to current physical position
    dribble_circle.x = physical->position.x;
    dribble_circle.y = physical->position.y - dribble_circle.radius;

    // set the control circle the same, but a bit forward...
    GameLib::Vector3 t(dribble_circle.x, dribble_circle.y);
    t = t + last_direction.getNormalizedToUnits() * close_control_circle.radius / 2;

    close_control_circle.x = t.x;
    close_control_circle.y = t.y;

    // debug
    //////////////////////////////////////////////////
    player_sprite->circle1.x = dribble_circle.x;
    player_sprite->circle1.y = dribble_circle.y;
    player_sprite->circle1.radius = dribble_circle.radius;

    player_sprite->circle2.x = close_control_circle.x;
    player_sprite->circle2.y = close_control_circle.y;
    player_sprite->circle2.radius = close_control_circle.radius;
    //////////////////////////////////////////////////
}

// ------------------------------------------------------------
// do_dribble
// ------------------------------------------------------------
void Player::do_dribble(const GameLib::Vector3 &direction) {
    // TODO height
    if (ball->physical->position.z > 30)
        return;

    // calc force needed for kick
    float force_needed = running_speed * 1.3f;
    GameLib::Vector3 kick = direction * force_needed;

    // normalize for diagonals
    float mag = kick.magnitude();

    // if magnitude is big enough
    if (mag > force_needed) {
        kick /= mag;
        kick *= force_needed;
    }

    // apply the kick force to ball
    ball->physical->ResetVelocity();
    ball->ApplyForce(kick);
}

// ------------------------------------------------------------
// do_close_control
// ------------------------------------------------------------
void Player::do_close_control() {
    // vector to store new ball position
    GameLib::Vector3 t = physical->position;

    // ball slighty in front of player in running direction
    t = t + last_direction.getNormalizedToUnits() * (close_control_circle.radius * 0.8f);

    // reset ball
    ball->physical->ResetVelocity();

    // set new position
    ball->physical->SetPosition(t);
}

// ------------------------------------------------------------
// ball_under_control
// ------------------------------------------------------------
bool Player::ball_under_control() {
    // true if ball is colliding with the control circle
    if (GameLib::CollisionDetector::collision(close_control_circle, ball->GetCollidable())) {
        return true;
    }
    return false;
}

// ------------------------------------------------------------
// kick
// ------------------------------------------------------------
void Player::kick(float force) {
    // players always kick in the direction they are facing
    GameLib::Vector3 direction = physical->velocity;
    direction.normalizeToUnits();
    GameLib::Vector3 kick_force = direction * force;
    kick_force.z = force * 0.3f;

    ball->ApplyForce(kick_force);
}

// ------------------------------------------------------------
// Call
// ------------------------------------------------------------
void Player::Call(std::vector<std::string> params) {
    if (params[0] == "arrive") {
        std::vector<std::string> new_params(params.begin() + 1, params.end());

        if (new_params.size() >= 2) {
            brain.locomotion.ActivateArrive(GameLib::Vector3(atoi(new_params[0].c_str()), atoi(new_params[1].c_str())));
        }
        return;
    }

    if (params[0] == "pursue") {
        std::vector<std::string> new_params(params.begin() + 1, params.end());
        if (new_params.size() >= 1) {
            GameEntity *entity = SenselessGame::game->GetEntity(new_params[0]);
            brain.locomotion.ActivatePursue(entity->physical);
        }
        return;
    }
    if (params[0] == "cover") {
        brain.locomotion.ActivateCover();
        return;
    }
    if (params[0] == "cancel") {
        brain.locomotion.Cancel();
        return;
    }
    GameLib::GameEntity::Call(params);
};

} // SenselessSoccer test
