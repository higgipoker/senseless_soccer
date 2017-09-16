#pragma once

#include <gamelib/game/game_entity.h>
#include <gamelib/utils/grid.h>

#include "../graphics/pitch_renderable.h"
#include "../metrics/metrics.h"

namespace SenselessSoccer {

class Pitch : public GameLib::GameEntity {
  public:
	/**
	* @brief constructor
	* @param x x
	* @param y y
	* @param width width
	* @param height height
	*/
	Pitch(GameLib::Physical *p, GameLib::Renderable *r, int x, int y, int width,
		  int height);

	/*
	 * @brief destruct
	 */
	~Pitch();

	/// grid system
	GameLib::Grid grid;

	/// pitch metrics
	PitchMetrics metrics;

  protected:
	/// renderable
	PitchTiled *renderable_pitch;
};

} // SenselessSoccer
