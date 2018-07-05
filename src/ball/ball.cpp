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
 * @file ball.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "ball.h"
#include <gamelib/math/constants.h>
#include <iostream>
#include "../metrics/metrics.h"

namespace SenselessSoccer {

const float GRAVITY = 9.8f;  // meters per second per second
const float AIR_FACTOR = 0.01f;
const float BALL_MASS = 400;  // mass doesnt matter, this is air resitance!
const int SHADOW_OFFSET = 1;

// ------------------------------------------------------------
// Ball
// ------------------------------------------------------------
Ball::Ball::Ball(GameLib::Physical *p, GameLib::Renderable *r)
    : GameLib::GameEntity(*p, *r),
      co_friction(0.98f),
      co_bounciness(0.7f),
      sprite_scale_factor(0.0),
      ball_sprite(static_cast<BallSprite &>(renderable)),
      ball_shadow(static_cast<BallShadowSprite &>(*ball_sprite.shadow)) {
  name = "ball";
  radius = 5;
  physical.dimensions.w = radius * 2;
  anchor_type = GameLib::ANCHOR_NONE;
  perspectivize = true;

  // for rotations
  ball_sprite.SetOrigin(ball_sprite.GetSize().w / 2,
                        ball_sprite.GetSize().w / 2);
  ball_shadow.SetOrigin(ball_shadow.GetSize().h / 2,
                        ball_shadow.GetSize().h / 2);
}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Ball::Update(float dt) {
  GameLib::GameEntity::Update(dt);

  // hz order
  renderable.z_order = static_cast<int>(physical.position.y);

  // ball physics
  do_physics(dt);

  // rolling animation
  ball_sprite.Animate();

  // shadow postion
  ball_shadow.SetPosition(physical.position.x + SHADOW_OFFSET,
                          physical.position.y + SHADOW_OFFSET);
}

// ------------------------------------------------------------
// Kickf
// ------------------------------------------------------------
void Ball::Kick(GameLib::Vector3 force) {
  physical.ResetAcceleration();
  physical.ResetVelocity();
  physical.acceleration = force;
}

// ------------------------------------------------------------
// apply_force
// ------------------------------------------------------------
void Ball::apply_force(GameLib::Vector3 force) {
  physical.acceleration += force;
}

// ------------------------------------------------------------
// do_physics
// ------------------------------------------------------------
void Ball::do_physics(float dt) {
  // formulas are in seconds, physics step is in "dt"
  float time_slice = dt / 1;

  // actual acceleration due to gravity for this time slice
  float gravity_act = GRAVITY * time_slice;

  // gravity
  if (physical.position.z > GameLib::TOL) {
    // change gravity meters into screen pixels
    float pixels_per_sec_squared = Metrics::MetersToPixels(gravity_act);

    // find gravity in pixels for one physics frame
    float grv = pixels_per_sec_squared;

    // make the gravity vector
    GameLib::Vector3 gravity(0, 0, -grv * BALL_MASS);

    // accumulate forces
    apply_force(gravity);
  }

  // friction
  else if (physical.velocity.z < GameLib::TOL &&
           physical.velocity.magnidude2d()) {
    physical.velocity *= co_friction;
  }

  // bounce
  else if (physical.position.z <= 0 && physical.velocity.z < 0) {
    // round off float unlimited bounce
    if (fabs(physical.position.z) < GameLib::TOL) {
      physical.position.z = 0;
      physical.velocity.z = 0;
      physical.acceleration.z = 0;
    } else {
      physical.velocity.z = -physical.velocity.z * co_bounciness;
    }
  }

  // basic euler is enough for our purposes
  physical.velocity += physical.acceleration * dt;
  physical.position += physical.velocity * dt;

  // reset acceleration ready for next frame
  physical.ResetAcceleration();
}

// ------------------------------------------------------------
// set_sprite_rotation
// ------------------------------------------------------------
void Ball::set_sprite_rotation() {
  ball_sprite.SetRotation(static_cast<int>(physical.GetAngle()));
}

// ------------------------------------------------------------
// rebound
// ------------------------------------------------------------
void Ball::rebound(GameLib::Vector3 wall, float damp, bool damp_z) {
  wall = wall.normalised();
  physical.velocity = physical.velocity.Reflect(wall);

  physical.velocity.x *= damp;
  physical.velocity.y *= damp;

  if (damp_z) {
    physical.velocity.z *= damp;
  }
}

// ------------------------------------------------------------
// Call
// ------------------------------------------------------------
void Ball::Call(std::vector<std::string> params) {
  GameLib::GameEntity::Call(params);
}
}  // namespace SenselessSoccer
