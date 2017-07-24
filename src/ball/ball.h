#pragma once

#include <gamelib/gamelib.h>
#include "../graphics/ball_sprite.h"

namespace SenselessSoccer {

class Ball : public GameLib::GameEntity {
public:

    /**
     * \brief constructor
     */
    Ball();

	/**
	 * \brief derived entities can do their own extra handling
	 * \param dt time delta
	 */
	virtual void Update( float dt ) override;

    /**
     * \brief apply a force to the ball
     * \param force force to apply
     */
    void ApplyForce(GameLib::Vector3 force);

    /**
     * \brief connect the player sprite
     */
    void ConnectSprite(BallSprite &sprite, BallShadowSprite &shadow);

	/**
	 * \brief get a collidable ball
	 */
	inline GameLib::Circle GetCollidable(){
		return GameLib::Circle( physical->position.x, physical->position.y, radius);
	}

	virtual void Call(std::vector<std::string> params) override;

protected:

    /**
     * \brief helper to do euler physics calcs etc
     * \param dt time delta
     */
    void do_physics(float dt);

	/**
	 * \brief set the sprite rotation depending on direction of roll
	 */
	void set_sprite_rotation();

	/**
	 * \brief rebound
	 * \param wall wall to bounce off
	 * \param damp damping
	 * \param damp_z extra damping in z
	 */
	void rebound(GameLib::Vector3 wall, float damp, bool damp_z);

	/// ball radius
    float radius;

	/// coefficient of friction
    float co_friction;

	/// coefficient of bounciness
    float co_bounciness;

    /// ball specific sprite
    BallSprite *ball_sprite;
	BallShadowSprite *ball_shadow;

	/// the scale factor of the ball when it's on the ground
	float sprite_scale_factor;

};

}// SenselessSoccer
