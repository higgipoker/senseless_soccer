#pragma once

#include <gamelib/game/game_entity.h>
#include "../graphics/ball_sprite.h"

namespace SenselessSoccer {

/**
 * @brief The Ball class
 */
class Ball : public GameLib::GameEntity {
 public:
  /**
   * @brief Ball
   * @param p
   * @param r
   */
  Ball(GameLib::Physical *p, GameLib::Renderable *r);

  /**
   * @brief Kick
   * @param force
   */
  void Kick(GameLib::Vector3 force);

  /**
   * @brief Update
   * @param dt
   */
  virtual void Update(float dt) override;

  /**
   * @brief GetCollidable
   * @return
   */
  inline GameLib::Circle GetCollidable() {
    return GameLib::Circle(physical.position.x, physical.position.y, radius);
  }

  /**
   * @brief Call
   * @param params
   */
  virtual void Call(std::vector<std::string> params) override;

 protected:
  /**
   * @brief apply_force
   * @param force
   */
  void apply_force(GameLib::Vector3 force);

  /**
   * @brief do_physics
   * @param dt
   */
  void do_physics(float dt);

  /**
   * @brief set_sprite_rotation
   */
  void set_sprite_rotation();

  /**
   * @brief rebound
   * @param wall
   * @param damp
   * @param damp_z
   */
  void rebound(GameLib::Vector3 wall, float damp, bool damp_z);

  float radius;
  float co_friction;
  float co_bounciness;
  float sprite_scale_factor;
  BallSprite &ball_sprite;
  BallShadowSprite &ball_shadow;
};

}  // namespace SenselessSoccer
