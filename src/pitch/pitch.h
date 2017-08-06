#pragma once

#include <gamelib/game/game_entity.h>
#include <gamelib/utils/grid.h>

#include "../graphics/pitch_renderable.h"
#include "../metrics/metrics.h"

namespace SenselessSoccer {

class Pitch : public GameLib::GameEntity {
  public:
    /**
    * \brief constructor
    * \param x x
    * \param y y
    * \param width width
    * \param height height
    */
    Pitch(int x, int y, int width, int height);

    /*
     * \brief destruct
     */
    ~Pitch();

    /**
    * \brief connect the pitch renderable
    * \param renderable reference to a renderable to use
    */
    void ConnectRenderable(PitchTiled &renderable);

    /// grid system
    GameLib::Grid grid;

    /// pitch metrics
    PitchMetrics metrics;

  protected:
    /// renderable
    PitchTiled *renderable_pitch;
};

} // SenselessSoccer
