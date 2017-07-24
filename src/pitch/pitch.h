#pragma once

#include <gamelib/game/game_entity.h>

#include "../metrics/metrics.h"
#include "../graphics/pitch_renderable.h"

namespace SenselessSoccer{

class Pitch : public GameLib::GameEntity{
public:

	/**
	* \brief constructor
	* \param x x
	* \param y y
	* \param width width
	* \param height height
	*/
	Pitch(int x, int y, int width, int height);

	/**
	* \brief connect the pitch renderable
	* \param renderable reference to a renderable to use
	*/
	void ConnectRenderable(PitchTiled &renderable);

protected:
	/// renderable
	PitchTiled *renderable_pitch;

	/// pitch metrics
	PitchMetrics metrics;
};

}// SenselessSoccer