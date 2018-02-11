/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file pitch_renderable.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include <gamelib/camera/camera.h>
#include <gamelib/graphics/tileset.h>

#include "../metrics/metrics.h"

namespace SenselessSoccer {

class PitchTiled : public GameLib::Tileset {
  public:
    /**
     * @brief construct
     * @param filename tile image file name
     * @param c camera for deciding what tiles to render
     */
    explicit PitchTiled(const std::string &filename, GameLib::Camera &c);

    /**
     * @brief specialized render function
     * @param window window to render to
     */
    virtual void Render(GameLib::Window &window) override;

    /**
     * @brief init the pitch metrics
     * @param m metrics
     */
    void InitMetrics(PitchMetrics m);

  private:
    PitchMetrics metrics;
    std::vector<GameLib::Line> lines;
};

} // SenselessSoccer
