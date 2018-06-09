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
#include <iostream>
#include "../metrics/metrics.h"

static const float INFINITE_SMALL_BOUNCE = 0.35f;

namespace SenselessSoccer {

const float TOL = 0.05f;     //  +/- as good as zero for float roudning errors
const float GRAVITY = 9.8f;  // meters per second per second
const float AIR_FACTOR = 0.01f;
const float BALL_MASS = 450;  // mass doesnt matter, this is air resitance!

// ------------------------------------------------------------
// Ball
// ------------------------------------------------------------
Ball::Ball::Ball(GameLib::Physical *p, GameLib::Renderable *r)
    : GameLib::GameEntity(*p, *r),
      radius(4),
      co_friction(0.01f),
      co_bounciness(-0.9f),
      sprite_scale_factor(0.0) {
  // local convenient access to subclassed ballsprite type of renderable
  ball_sprite = static_cast<BallSprite *>(&renderable);
  ball_shadow = static_cast<BallShadowSprite *>(ball_sprite->shadow);

  // for rotations
  ball_sprite->SetOrigin(ball_sprite->GetSize().w / 2,
                         ball_sprite->GetSize().w / 2);
  ball_shadow->SetOrigin(ball_shadow->GetSize().h / 2,
                         ball_shadow->GetSize().h / 2);

  name = "ball";
  anchor_type = GameLib::ANCHOR_NONE;
}

// ------------------------------------------------------------
// ~Ball
// ------------------------------------------------------------
Ball::~Ball() {}

// tmp
const int SHADOW_OFFSET = 1;
static const float PI = 3.14159265359f;
#define DEGREES(a) a *(180.0f / PI)
// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Ball::Update(float dt) {
  GameLib::GameEntity::Update(dt);

  // hz order
  renderable.z_order = static_cast<int>(physical.position.y);

  // ball physics
  do_physics(dt);

  // if the screen width is 800, then 1 degree is 4.44 pixels
  float angular_pixel = 4;

  float z_position = physical.position.z;
  float ball_diameter_at_zero = radius * 2;
  float ball_diameter = 14.0;
  float camera_height = 100;
  float dist_from_camera = camera_height - physical.position.z;
  float angular_diameter = 2 * (atanf(ball_diameter / (2 * dist_from_camera)));
  float degs = DEGREES(angular_diameter);
  float angular_pixels = degs * angular_pixel;

  sprite_scale_factor = angular_pixels / 60;
  ball_sprite->Scale(sprite_scale_factor);

  // scale ball sprite depending on height
  //  sprite_scale_factor = radius * 2 / ball_sprite->GetSize().w *
  //                        (1 + (physical.position.z * 0.01f));
  //  ball_sprite->Scale(sprite_scale_factor);

  // the ball only rolls if it's moving
  // if (physical.velocity.magnidude2d() > GameLib::TOL) {

  // rotate ball sprite depending on roll direction
   set_sprite_rotation();
   ball_sprite->Animate();


  // y offset due to height

  // shadow postion
  int shadow_x = physical.position.x + SHADOW_OFFSET;
  int shadow_y = physical.position.y + SHADOW_OFFSET;

  if (shadow_y < physical.position.y || shadow_x < physical.position.x) {
    // std::cout << "oops" << std::endl;
  }

  ball_shadow->SetPosition(shadow_x, shadow_y);

  //  // shadow size
  ball_shadow->Scale(sprite_scale_factor);

  if (recording) {
    if (velocity.magnitude() < GameLib::TOL) {
      recording = false;
      // GameLib::Vector3 dist = physical.position - start_record;
    }
  }
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
  // how many dts in one second?
  float chunk = 1 / dt;

  // change meters into screen pixels
  float pixels_per_sec_squared = Metrics::MetersToPixels(GRAVITY);

  // find gravity in pixels for one physics frame
  float grv = pixels_per_sec_squared / chunk;

  float ms = BALL_MASS / chunk;

  // either gravity or friction
  if (physical.position.z > GameLib::TOL) {
    // gravity
    GameLib::Vector3 gravity(0, 0, -grv * ms);
    apply_force(gravity);

    // air resistance
    if (physical.velocity.magnidude2d() > GameLib::TOL) {
      float air_resistance = physical.position.z * AIR_FACTOR;
      GameLib::Vector3 air = physical.velocity.Reverse() * air_resistance;
      apply_force(air);
    }
  } else if(physical.velocity.magnidude2d() >TOL){
    physical.position.z = 0;
    physical.velocity.z = 0;
    physical.acceleration.z = 0;
    // friction
    GameLib::Vector3 friction = physical.velocity.Reverse();
    friction *= co_friction;
    apply_force(friction);
  }

  physical.velocity += physical.acceleration * dt;
  physical.position += physical.velocity * dt;

  // bounce
  if (physical.position.z < 0 && physical.velocity.z < 0) {
    physical.position.z = 0;
    physical.velocity.z = -physical.velocity.z * 0.98f;
  }
}

// ------------------------------------------------------------
// set_sprite_rotation
// ------------------------------------------------------------
void Ball::set_sprite_rotation() {
  ball_sprite->SetRotation(static_cast<int>(physical.GetAngle()));
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

// ------------------------------------------------------------
// StartRecordDistance
// ------------------------------------------------------------
void Ball::StartRecordDistance() {
  recording = true;
  start_record = physical.position;
}
}  // namespace SenselessSoccer
