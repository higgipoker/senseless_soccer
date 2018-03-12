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
#include "../metrics/metrics.h"
#include <iostream>

static const float INFINITE_SMALL_BOUNCE = 0.35f;

namespace SenselessSoccer {

/// as good as zero
const float TOL = 0.05f;
const float GRAVITY = 9.8f;
const float AIR_FACTOR = 0.02f;
const float BALL_MASS = 12.0f;

// ------------------------------------------------------------
// Ball
// ------------------------------------------------------------
Ball::Ball::Ball(GameLib::Physical *p, GameLib::Renderable *r)
    : GameLib::GameEntity(*p, *r), radius(3), co_friction(2.6f), co_bounciness(0.7f),
      sprite_scale_factor(0.0) {

    // local convenient access to subclassed ballsprite type of renderable
    ball_sprite = static_cast<BallSprite *>(&renderable);
    ball_shadow = static_cast<BallShadowSprite *>(ball_sprite->shadow);

    // for rotations
    ball_sprite->SetOrigin(ball_sprite->GetWidth() / 2, ball_sprite->GetHeight() / 2);
    ball_shadow->SetOrigin(ball_shadow->GetWidth() / 2, ball_shadow->GetHeight() / 2);

    name = "ball";
    anchor_type = GameLib::ANCHOR_NONE;
}

// ------------------------------------------------------------
// ~Ball
// ------------------------------------------------------------
Ball::~Ball() {}

// tmp
const int SHADOW_OFFSET = 2;

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Ball::Update(float dt) {
    GameLib::GameEntity::Update(dt);

    // hz order
    renderable.z_order = static_cast<int>(physical.position.y);

    // ball physics
    do_physics(dt);

    // scale ball sprite depending on height
    sprite_scale_factor =
        radius * 2 / ball_sprite->GetWidth() * (1 + (physical.position.z * 0.02f));
    ball_sprite->Scale(sprite_scale_factor);

    // the ball only rolls if it's moving
    if (physical.velocity.magnitude() > 0.2f) {

        // rotate ball sprite depending on roll direction
        set_sprite_rotation();
        ball_sprite->Animate();
    }

    // shadow postion
    ball_shadow->SetPosition(
        ball_sprite->GetPosition().x + SHADOW_OFFSET + physical.position.z * 0.5f,
        ball_sprite->GetPosition().y + SHADOW_OFFSET + physical.position.z * 0.5f);

    // shadow size
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
void Ball::apply_force(GameLib::Vector3 force) { physical.acceleration += force; }

// ------------------------------------------------------------
// do_physics
// ------------------------------------------------------------
void Ball::do_physics(float dt) {

    // either gravity or friction
    if (physical.position.z > 0) {

        // gravity
        GameLib::Vector3 gravity(0, 0, -GRAVITY * BALL_MASS);
        apply_force(gravity);

        // air resistance
        if (physical.velocity.magnidude2d() > GameLib::TOL) {
            float air_resistance = physical.position.z * AIR_FACTOR;
            GameLib::Vector3 air = physical.velocity.Reverse() * air_resistance;
            apply_force(air);
        }

    } else {
        // friction
        GameLib::Vector3 friction = physical.velocity.Reverse();
        friction *= co_friction;
        friction.z = 0;
        apply_force(friction);
    }

    // bounce if sufficiently low,and moving down
    if (physical.position.z < GameLib::TOL && physical.velocity.z < GameLib::TOL) {
        physical.position.z = 0;
        physical.velocity.z = -(physical.velocity.z * co_bounciness);
    }

    // improved euler
    physical.velocity += physical.acceleration * dt;
    GameLib::Vector3 next_velocity = physical.velocity + physical.acceleration * dt;
    physical.position += physical.velocity + next_velocity * 0.5 * dt;
    physical.ResetAcceleration();
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
void Ball::Call(std::vector<std::string> params) { GameLib::GameEntity::Call(params); }

// ------------------------------------------------------------
// StartRecordDistance
// ------------------------------------------------------------
void Ball::StartRecordDistance() {
    recording = true;
    start_record = physical.position;
}
} // SenselessSoccer
