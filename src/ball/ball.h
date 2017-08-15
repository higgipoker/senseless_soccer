#pragma once

#include <gamelib/game/game_entity.h>
#include "../graphics/ball_sprite.h"

namespace SenselessSoccer {

class Ball : public GameLib::GameEntity {
public:
    Ball();

    virtual void Update(float dt) override;
    void ApplyForce(GameLib::Vector3 force);
    void ConnectSprite(BallSprite &sprite, BallShadowSprite &shadow);
    inline GameLib::Circle GetCollidable() {
        return GameLib::Circle(physical->position.x, physical->position.y, radius);
    }
    virtual void Call(std::vector<std::string> params) override;

protected:
    void do_physics(float dt);
    void set_sprite_rotation();
    void rebound(GameLib::Vector3 wall, float damp, bool damp_z);

    float radius;
    float co_friction;
    float co_bounciness;
    BallSprite *ball_sprite;
    BallShadowSprite *ball_shadow;
    float sprite_scale_factor;
};

} // SenselessSoccer
