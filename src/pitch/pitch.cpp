#include "pitch.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Pitch::Pitch(GameLib::Physical *p, GameLib::Renderable *r, int x, int y,
			 int width, int height)
 : GameLib::GameEntity(p, r)
 , grid(x, y, width, height, 15, 19) {

	metrics.Init(x, y, width, height);
	renderable_pitch = static_cast<PitchTiled *>(renderable);
	renderable_pitch->InitMetrics(metrics);
	name = "pitch";
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Pitch::~Pitch() {
}

} // SenselessSoccer
