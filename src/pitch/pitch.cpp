#include "pitch.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Pitch::Pitch (int x, int y, int width, int height) {
	name = "pitch";
	metrics.Init (x, y, width, height);
}

// ------------------------------------------------------------
// ConnectRenderable
// ------------------------------------------------------------
void Pitch::ConnectRenderable (PitchTiled &renderable) {
	this->renderable = &renderable;
	renderable_pitch = &renderable;

	renderable_pitch->InitMetrics (metrics);
}

}// SenselessSoccer
