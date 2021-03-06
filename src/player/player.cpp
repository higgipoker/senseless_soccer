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
 * @file player.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "player.h"

#include <gamelib/physics/collision_detector.h>

#include "../game/game.h"
#include "../globals.h"
#include "../team/team.h"
#include "locomotion/arrive.h"
#include "locomotion/pursue.h"
#include "player_states/standing.h"

using GameLib::Vector3;

namespace SenselessSoccer {

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
Player::Player(GameLib::Physical *p, GameLib::Renderable *r)
  : GameLib::GameEntity(*p, *r)
  ,

  /// specific player sprite
  player_sprite(static_cast<PlayerSprite *>(r))
  ,

  /// a brain
  brain(*this)
  ,

  // default dribble radius
  dribble_circle(0, 0, 4)
  ,

  // default control radius
  close_control_circle(0, 0, 8) {
    // player sprites annchor to bottom of image (postion rofers to feet)
    anchor_type = GameLib::ANCHOR_BASELINE;

    // initialize state machine
    InitState(new Standing(*me));
}

// -----------------------------------------------------------------------------
// Update
// -----------------------------------------------------------------------------
void Player::Update(float dt) {
    GameLib::GameEntity::Update(dt);
    GameLib::StateMachine::Step(dt);

    // z order
    renderable.z_order = physical.position.y;

    // distance from ball
    distance_from_ball =
      (physical.position - ball->physical.position).magnitude();

    // input is attached
    if (input) {
        static_cast<PlayerState *>(current_state)->handle_input();

    } else {
        brain.Step(dt);
    }

    // update the player position
    update_position(dt);

    // update the sprite animation
    animate_sprite();

    // update dribble circle
    update_dribble_circle();

    // calc if changed direction
    if (last_direction.equals(velocity.getNormalizedToUnits())) {
        changed_direction = false;

    } else {
        changed_direction = true;
    }

    // save direction
    if (velocity.magnitude() > GameLib::TOL) {
        last_direction = velocity.getNormalizedToUnits();
    }

    // ball control
    if (changed_direction && ball_under_control() &&
        velocity.magnitude() > GameLib::TOL) {
        do_close_control();
    }

    if (my_team->key_players.player_in_possession == me) {
        calc_pass_recipients();

    } else {
        player_sprite->triangle1.p1 = GameLib::Point(0, 0);
        player_sprite->triangle1.p2 = GameLib::Point(0, 0);
        player_sprite->triangle1.p3 = GameLib::Point(0, 0);
    }

    // set the label
    if (input) {
        player_sprite->text.SetText("PLAYER 1");

    } else {
        // player_sprite->text.SetText(brain.statename);
        player_sprite->text.SetText(name);
    }
}

// -----------------------------------------------------------------------------
// AttachInput
// -----------------------------------------------------------------------------
void Player::AttachInput(Controller *i) {
    input = i;
    input->AddListener(me);
}

// -----------------------------------------------------------------------------
// DetatchInput
// -----------------------------------------------------------------------------
void Player::DetatchInput() {
    input->RemoveListener(me);
    // null means no input attached to this player
    input = nullptr;
}

// -----------------------------------------------------------------------------
// update_position
// -----------------------------------------------------------------------------
void Player::update_position(float dt) {
    // normalises velocity for consistent speed in diagonals
    normalize_velocity();

    // update position according to velocity and individual running speed
    physical.position += velocity * dt * running_speed;
}

// -----------------------------------------------------------------------------
// normalize_velocity
// -----------------------------------------------------------------------------
void Player::normalize_velocity() {
    // normalises to units
    velocity.normalise();

    // normalizes for diagonals
    if (velocity.magnitude() > running_speed) {
        velocity *= running_speed;
    }
}

// -----------------------------------------------------------------------------
// animate
// -----------------------------------------------------------------------------
void Player::animate_sprite() {
    // poll animation
    player_sprite->Animate();

    // update shadow
    if (player_sprite->shadow) {
        // TODO magic numbers here for shadow offset
        player_sprite->shadow->SetPosition(player_sprite->GetPosition().x + 3,
                                           player_sprite->GetPosition().y + 7);
    }
}

// -----------------------------------------------------------------------------
// update_dribble_circle
// -----------------------------------------------------------------------------
void Player::update_dribble_circle() {
    // set dribble circle to current physical position
    dribble_circle.x = physical.position.x;
    dribble_circle.y = physical.position.y - dribble_circle.radius;

    // set the control circle the same, but a bit forward...
    Vector3 t(dribble_circle.x, dribble_circle.y);
    t = t +
      last_direction.getNormalizedToUnits() * close_control_circle.radius / 2;

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

// -----------------------------------------------------------------------------
// do_dribble
// -----------------------------------------------------------------------------
void Player::do_dribble(const Vector3 &direction) {
    // TODO height
    if (ball->physical.position.z > 30)
        return;

    gained_possession();

    // calc force needed for kick
    float force_needed = running_speed * 120.0f;
    Vector3 kick = direction * force_needed;

    // normalize for diagonals
    if (kick.magnitude() > force_needed) {
        kick /= kick.magnitude();
        kick *= force_needed;
    }

    // apply the kick force to ball
    ball->Kick(kick);
}

// -----------------------------------------------------------------------------
// do_slide_tackle
// -----------------------------------------------------------------------------
void Player::do_slide_tackle(const Vector3 &direction) {
    // TODO height
    if (ball->physical.position.z > 30)
        return;

    // calc force needed for kick
    float force_needed = running_speed * 1.2f;
    Vector3 kick = direction * force_needed;

    // normalize for diagonals
    if (kick.magnitude() > force_needed) {
        kick /= kick.magnitude();
        kick *= force_needed;
    }

    // apply the kick force to ball
    ball->Kick(kick);

    gained_possession();
}

// -----------------------------------------------------------------------------
// do_close_control
// -----------------------------------------------------------------------------
void Player::do_close_control() {
    // vector to store new ball position
    Vector3 t = physical.position;

    // ball slighty in front of player in running direction
    t = t +
      last_direction.getNormalizedToUnits() *
        (close_control_circle.radius * 0.1f);

    // reset ball
    ball->physical.ResetVelocity();

    // set new position
    ball->physical.SetPosition(t);
}

// -----------------------------------------------------------------------------
// ball_under_control
// -----------------------------------------------------------------------------
bool Player::ball_under_control() {
    // true if ball is colliding with the control circle
    if (GameLib::CollisionDetector::collision(close_control_circle,
                                              ball->GetCollidable())) {
        return true;
    }

    lost_possession();
    return false;
}

// -----------------------------------------------------------------------------
// kick
// -----------------------------------------------------------------------------
void Player::kick(float force) {
    std::cout << "force: " << force << std::endl;

    // players always kick in the direction they are facing
    Vector3 direction = last_direction;
    direction.normalizeToUnits();

    if (my_team->key_players.short_pass_candidates.size()) {
        Vector3 dist = physical.position -
          my_team->key_players.short_pass_candidates[0]->physical.position;
        float mag = dist.magnitude();
        float meters = Metrics::PixelsToMeters(mag);

        force = Metrics::force_per_meter * meters;

        direction =
          my_team->key_players.short_pass_candidates[0]->physical.position -
          physical.position;
        direction.normalise();

    } else {
        // TODO upscale fire length
        force *= 1.6f;
    }

    Vector3 kick_force = direction * force;
    kick_force.z = force * 1.8f;
    ball->Kick(kick_force);
}

// -----------------------------------------------------------------------------
// ShortPass
// -----------------------------------------------------------------------------
void Player::short_pass() {
    float force = 0;
    Vector3 dist = physical.position -
      my_team->key_players.short_pass_candidates[0]->physical.position;
    float mag = dist.magnitude();
    float meters = Metrics::PixelsToMeters(mag);
    force = Metrics::force_per_meter * meters;
    Vector3 direction =
      my_team->key_players.short_pass_candidates[0]->physical.position -
      physical.position;
    direction.normalise();
    Vector3 kick_force = direction * force;
    kick_force.z = force * 0.1f;
    ball->Kick(kick_force);
}

// -----------------------------------------------------------------------------
// OnGainedPosession
// -----------------------------------------------------------------------------
void Player::gained_possession() {
    my_team->OnGotPossession(me);
    running_speed = DEFAULT_SPEED;
}

// -----------------------------------------------------------------------------
// OnLostPossession
// -----------------------------------------------------------------------------
void Player::lost_possession() {
    my_team->OnLostPossession(me);
    running_speed = DEFAULT_SPEED;
}

// -----------------------------------------------------------------------------
// Shoot
// -----------------------------------------------------------------------------
void Player::shoot() {
    Vector3 target(pitch->metrics.north_goal.x1, pitch->metrics.north_goal.y1);
    target.x +=
      rand() % int(pitch->metrics.north_goal.x2 - pitch->metrics.north_goal.x1);
    Vector3 shot_direction = (target - physical.position);
    shot_direction.normalise();
    Vector3 force = shot_direction;
    float power = 20000;
    force *= power;
    force.z = power * 0.1f;
    ball->Kick(force);
}

// -----------------------------------------------------------------------------
// Clearance
// -----------------------------------------------------------------------------
void Player::clearance() {
    // TODO: a clearance direction
    Vector3 target(pitch->metrics.north_goal.x1, pitch->metrics.north_goal.y1);
    target.x +=
      rand() % int(pitch->metrics.north_goal.x2 - pitch->metrics.north_goal.x1);
    Vector3 shot_direction = (target - physical.position);
    shot_direction.normalise();
    Vector3 force = shot_direction;
    float power = 10000;
    force *= power;
    force.z = power * 0.4f;
    ball->Kick(force);
}

// -----------------------------------------------------------------------------
// calc_pass_recipients
// -----------------------------------------------------------------------------
//  --------------------------------------------------
//       [PLAYER]
//
//          p1
//          /\
//         /  \
//        /    \
//       /      \
//     p2--------p3
//
//  calc_pass_recipients
//  --------------------------------------------------
void Player::calc_pass_recipients() {
    Vector3 tmp = physical.position;
    tmp = tmp + velocity.normalised() * 20;
    Vector3 temp1 = last_direction;
    Vector3 temp2 = last_direction;
    Vector3 t1 =
      physical.position + (temp1.rotated(35, 0, 0)).normalised() * 400;
    Vector3 t2 =
      physical.position + (temp2.rotated(-35, 0, 0)).normalised() * 400;

    player_sprite->triangle1.p1 = GameLib::Point(tmp.x, tmp.y);
    player_sprite->triangle1.p2 = GameLib::Point(t1.x, t1.y);
    player_sprite->triangle1.p3 = GameLib::Point(t2.x, t2.y);

    if (player_sprite->triangle1.p1.x < 0)
        player_sprite->triangle1.p1.x = 0;

    if (player_sprite->triangle1.p1.y < 0)
        player_sprite->triangle1.p1.y = 0;

    if (player_sprite->triangle1.p2.x < 0)
        player_sprite->triangle1.p2.x = 0;

    if (player_sprite->triangle1.p2.y < 0)
        player_sprite->triangle1.p2.y = 0;

    if (player_sprite->triangle1.p3.x < 0)
        player_sprite->triangle1.p3.x = 0;

    if (player_sprite->triangle1.p3.y < 0)
        player_sprite->triangle1.p3.y = 0;

    player_sprite->triangle1_color(255, 0, 0, 100);
    my_team->key_players.short_pass_candidates.clear();

    for (auto player : my_team->players) {
        if (player == me)
            continue;

        if ((me->physical.position - player->physical.position).magnitude() <
            100)
            continue;

        if (GameLib::CollisionDetector::collision(
              player->physical.position.ToPoint(), player_sprite->triangle1)) {
            player_sprite->triangle1_color(0, 255, 0, 100);
            my_team->key_players.short_pass_candidates.push_back(player);
        }
    }
}

// -----------------------------------------------------------------------------
// DoSlideTackle
// -----------------------------------------------------------------------------
void Player::slide_tackle() {
    sliding = true;
}

// -----------------------------------------------------------------------------
// OnControllerEvent
// -----------------------------------------------------------------------------
void Player::OnControllerEvent(ControllerEvent event) {
    (static_cast<PlayerState *>(current_state))->HandleEvent(event);
}

// -----------------------------------------------------------------------------
// Call
// -----------------------------------------------------------------------------
void Player::Call(std::vector<std::string> params) {
    if (params[0] == "arrive") {
        std::vector<std::string> new_params(params.begin() + 1, params.end());

        if (new_params.size() >= 2) {
            brain.locomotion.ActivateArrive(Vector3(
              atoi(new_params[0].c_str()), atoi(new_params[1].c_str())));
        }

        return;
    }

    if (params[0] == "pursue") {
        std::vector<std::string> new_params(params.begin() + 1, params.end());

        if (new_params.size() >= 1) {
            GameEntity entity = Globals::sensi->GetEntity(new_params[0]);
            brain.locomotion.ActivatePursue(entity.physical);
        }

        return;
    }

    if (params[0] == "cover") {
        brain.ActivateState(BRAIN_COVER);
        return;
    }

    if (params[0] == "support") {
        brain.ActivateState(BRAIN_SUPPORT);
        return;
    }

    if (params[0] == "retrieve") {
        brain.ActivateState(BRAIN_GETBALL);
        return;
    }

    if (params[0] == "clearance") {
        brain.ActivateState(BRAIN_CLEAR);
        return;
    }

    if (params[0] == "head") {
        std::vector<std::string> new_params(params.begin() + 1, params.end());

        if (new_params.size() >= 1) {
            Vector3 dir;

            if (new_params[0] == "north") {
                dir = Metrics::compasstoVector(NORTH);

            } else if (new_params[0] == "north_east") {
                dir = Metrics::compasstoVector(NORTH_EAST);

            } else if (new_params[0] == "east") {
                dir = Metrics::compasstoVector(EAST);

            } else if (new_params[0] == "south_east") {
                dir = Metrics::compasstoVector(SOUTH_EAST);

            } else if (new_params[0] == "south") {
                dir = Metrics::compasstoVector(SOUTH);

            } else if (new_params[0] == "south_west") {
                dir = Metrics::compasstoVector(SOUTH_WEST);

            } else if (new_params[0] == "west") {
                dir = Metrics::compasstoVector(WEST);

            } else if (new_params[0] == "north_west") {
                dir = Metrics::compasstoVector(NORTH_WEST);
            }

            brain.locomotion.ActivateHead(dir);
        }

        return;
    }

    if (params[0] == "modify") {
        std::vector<std::string> new_params(params.begin() + 1, params.end());

        if (new_params.size() >= 1) {
            brain.SetModifier(modifier(atoi(new_params[0].c_str())));
        }
    }

    if (params[0] == "cancel") {
        brain.locomotion.Cancel();
        return;
    }

    GameLib::GameEntity::Call(params);
}

// -----------------------------------------------------------------------------
// distance_to_goal
// -----------------------------------------------------------------------------
float Player::distance_to_goal() {
    Vector3 goal_center(pitch->metrics.north_goal.x1,
                        pitch->metrics.north_goal.y1);
    goal_center.x +=
      (pitch->metrics.north_goal.x2 - pitch->metrics.north_goal.x1) / 2;
    return (physical.position - goal_center).magnitude();
}

// -----------------------------------------------------------------------------
// AddtoTeam
// -----------------------------------------------------------------------------
void Player::AddtoTeam(Team *_my_team, Team *_other_team, Ball *_ball,
                       Pitch *_pitch) {
    my_team = _my_team;
    other_team = _other_team;
    ball = _ball;
    pitch = _pitch;
}

} // namespace SenselessSoccer
