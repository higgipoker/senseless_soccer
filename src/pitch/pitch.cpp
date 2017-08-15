#include "pitch.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Constructor
// ------------------------------------------------------------
Pitch::Pitch(int x, int y, int width, int height) : grid(x, y, width, height, 15, 19) {
    name = "pitch";
    physical = new GameLib::Physical();
    metrics.Init(x, y, width, height);
}

// ------------------------------------------------------------
// Destructor
// ------------------------------------------------------------
Pitch::~Pitch() {
    delete physical;
}

// ------------------------------------------------------------
// ConnectRenderable
// ------------------------------------------------------------
void Pitch::ConnectRenderable(PitchTiled &renderable) {
    this->renderable = &renderable;
    renderable_pitch = &renderable;

    renderable_pitch->InitMetrics(metrics);
}

}  // SenselessSoccer
