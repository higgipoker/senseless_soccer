#include "ball.h"
#include "../metrics/metrics.h"
#include <iostream>

static const float INFINITE_SMALL_BOUNCE = 0.35f;

namespace SenselessSoccer {

/// as good as zero
const float TOL = 0.05f;
const float GRAVITY = 98.0f;
const float AIR_FACTOR = 0.04f;

// ------------------------------------------------------------
// Ball
// ------------------------------------------------------------
Ball::Ball::Ball(GameLib::Physical *p, GameLib::Renderable *r)
    : GameLib::GameEntity(p, r)
    , radius(3)
    , co_friction(30)
    , co_bounciness(0.7f)
    , sprite_scale_factor(0.0f) {

    // local convenient access to subclassed ballsprite type of renderable
    ball_sprite = static_cast<BallSprite *>(renderable);
    ball_shadow = static_cast<BallShadowSprite *>(renderable->shadow);

    // for rotations
    ball_sprite->SetOrigin(ball_sprite->GetWidth() / 2, ball_sprite->GetHeight() / 2);
    ball_shadow->SetOrigin(ball_shadow->GetWidth() / 2, ball_shadow->GetHeight() / 2);

    name = "ball";
    anchor_type = GameLib::ANCHOR_NONE;
}

// ------------------------------------------------------------
// ~Ball
// ------------------------------------------------------------
Ball::~Ball() {
}

// tmp
const int SHADOW_OFFSET = 2;

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Ball::Update(float dt) {
    GameLib::GameEntity::Update(dt);

    // hz order
    renderable->z_order = physical->position.y;

    // ball physics
    do_physics(dt);

    // scale ball sprite depending on height
    sprite_scale_factor = radius * 2 / ball_sprite->GetWidth() * (1 + (physical->position.z * 0.1));
    ball_sprite->Scale(sprite_scale_factor);

    // the ball only rolls if it's moving
    if(physical->velocity.magnitude() > TOL) {

        // rotate ball sprite depending on roll direction
        set_sprite_rotation();

        // step the animation
        ball_sprite->Animate();
    }

    // shadow postion
    ball_shadow->SetPosition(ball_sprite->GetPosition().x + SHADOW_OFFSET + physical->position.z,
                             ball_sprite->GetPosition().y + SHADOW_OFFSET + physical->position.z);

    // shadow size
    ball_shadow->Scale(sprite_scale_factor);

    if(recording) {
        if(velocity.magnitude() < 0.2f) {
            recording = false;
            GameLib::Vector3 dist = physical->position - start_record;
        }
    }
}

// ------------------------------------------------------------
// Kick
// ------------------------------------------------------------
void Ball::Kick(GameLib::Vector3 force) {
    physical->ResetAcceleration();
    physical->ResetVelocity();
    physical->acceleration = force;
}

// ------------------------------------------------------------
// apply_force
// ------------------------------------------------------------
void Ball::apply_force(GameLib::Vector3 force) {
    physical->acceleration += force;
}

// ------------------------------------------------------------
// do_physics
// ------------------------------------------------------------
void Ball::do_physics(float dt) {

    // either gravity or friction
    if(physical->position.z > 0) {

        // gravity
        GameLib::Vector3 gravity(0, 0, -GRAVITY);
        apply_force(gravity);

        // air resistance
        float air_resistance = physical->position.z * AIR_FACTOR;
        GameLib::Vector3 air = physical->velocity.Reverse() * air_resistance;
        apply_force(air);

    } else if(physical->velocity.magnitude()) {

        // friction
        GameLib::Vector3 friction = physical->velocity.Reverse();
        friction *= co_friction;
        friction.z = 0;
        apply_force(friction);
    }

    // bounce
    if(physical->position.z <= 0 && physical->velocity.z) {
        physical->position.z = 0;
        physical->velocity.z = -(physical->velocity.z * co_bounciness);

        // infinite bounce damping
        if(fabs(physical->velocity.z) < INFINITE_SMALL_BOUNCE) {
            physical->velocity.z = 0;
            physical->position.z = 0;
        }
    }

    // improved euler
    physical->velocity += physical->acceleration * dt;
    GameLib::Vector3 next_velocity = physical->velocity + physical->acceleration * dt;
    physical->position += physical->velocity + next_velocity * 0.5f * dt;
    physical->ResetAcceleration();
}

// ------------------------------------------------------------
// set_sprite_rotation
// ------------------------------------------------------------
void Ball::set_sprite_rotation() {
    ball_sprite->SetRotation(physical->GetAngle());
}

// ------------------------------------------------------------
// rebound
// ------------------------------------------------------------
void Ball::rebound(GameLib::Vector3 wall, float damp, bool damp_z) {
    wall = wall.normalised();
    physical->velocity = physical->velocity.Reflect(wall);

    physical->velocity.x *= damp;
    physical->velocity.y *= damp;

    if(damp_z) {
        physical->velocity.z *= damp;
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
    start_record = physical->position;
}
} // SenselessSoccer
