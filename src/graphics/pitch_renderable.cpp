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
 * @file pitch_renderable.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "pitch_renderable.h"

#include <gamelib/graphics/primitives.h>
#include <gamelib/math/shapes.h>
#include <iostream>

namespace SenselessSoccer {

// ------------------------------------------------------------
// Pitchtiled
// ------------------------------------------------------------
PitchTiled::PitchTiled(const std::string &filename, GameLib::Camera &c)
    : GameLib::Tileset(filename, c) {
    z_order = 1;
}
// ------------------------------------------------------------
// Render
// ------------------------------------------------------------
void PitchTiled::Render(GameLib::Window &window) {
    if (!metrics.inited)
        return;

    GameLib::Tileset::Render(window);

    // white lines
    GameLib::Primitives::OutlineColor(GameLib::Color(255, 255, 255, 200));

    unsigned int thickness = 2;

    //
    // pitch perimiter
    //
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x, metrics.pitch_rect.y),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w,
                         metrics.pitch_rect.y),
        thickness);
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w,
                                 metrics.pitch_rect.y),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w,
                         metrics.pitch_rect.y + metrics.pitch_rect.h),
        thickness);
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w,
                                 metrics.pitch_rect.y + metrics.pitch_rect.h),
        GameLib::Vector3(metrics.pitch_rect.x,
                         metrics.pitch_rect.y + metrics.pitch_rect.h),
        thickness);
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x,
                                 metrics.pitch_rect.y + metrics.pitch_rect.h),
        GameLib::Vector3(metrics.pitch_rect.x, metrics.pitch_rect.y), thickness);

    //
    // cetner line
    //
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x,
                                 metrics.pitch_rect.y + metrics.pitch_rect.h / 2),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w,
                         metrics.pitch_rect.y + metrics.pitch_rect.h / 2),
        thickness);

    //
    // north box 18
    //
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                                     Metrics::YardsToPixels(22),
                                 metrics.pitch_rect.y),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                             Metrics::YardsToPixels(22),
                         metrics.pitch_rect.y + Metrics::YardsToPixels(18)),
        thickness);

    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                                     Metrics::YardsToPixels(22),
                                 metrics.pitch_rect.y + Metrics::YardsToPixels(18)),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22),
                         metrics.pitch_rect.y + Metrics::YardsToPixels(18)),
        thickness);

    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                                     Metrics::YardsToPixels(22),
                                 metrics.pitch_rect.y + Metrics::YardsToPixels(18)),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22),
                         metrics.pitch_rect.y),
        thickness);

    //
    // north box 6
    //
    GameLib::Primitives::DrawLine(
        window,
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                             Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                             Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + Metrics::YardsToPixels(6)),
        thickness);

    GameLib::Primitives::DrawLine(
        window,
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                             Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + Metrics::YardsToPixels(6)),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + Metrics::YardsToPixels(6)),
        thickness);

    GameLib::Primitives::DrawLine(
        window,
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + Metrics::YardsToPixels(6)),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y),
        thickness);

    //
    // south box 18
    //
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                                     Metrics::YardsToPixels(22),
                                 metrics.pitch_rect.y + metrics.pitch_rect.h),
        GameLib::Vector3(
            metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels(22),
            metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels(18)),
        thickness);

    GameLib::Primitives::DrawLine(
        window,
        GameLib::Vector3(
            metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels(22),
            metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels(18)),
        GameLib::Vector3(
            metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels(22),
            metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels(18)),
        thickness);

    GameLib::Primitives::DrawLine(
        window,
        GameLib::Vector3(
            metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels(22),
            metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels(18)),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22),
                         metrics.pitch_rect.y + metrics.pitch_rect.h),
        thickness);

    //
    // south box 6
    //
    GameLib::Primitives::DrawLine(
        window,
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                             Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + metrics.pitch_rect.h),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                             Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + metrics.pitch_rect.h -
                             Metrics::YardsToPixels(6)),
        thickness);

    GameLib::Primitives::DrawLine(
        window,
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
                             Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + metrics.pitch_rect.h -
                             Metrics::YardsToPixels(6)),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + metrics.pitch_rect.h -
                             Metrics::YardsToPixels(6)),
        thickness);

    GameLib::Primitives::DrawLine(
        window,
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + metrics.pitch_rect.h -
                             Metrics::YardsToPixels(6)),
        GameLib::Vector3(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
                             Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
                         metrics.pitch_rect.y + metrics.pitch_rect.h),
        thickness);

    //
    // center circle
    //
    GameLib::Primitives::OutlineColor(GameLib::Color(255, 255, 255, 100));
    GameLib::Primitives::Arc(window, metrics.pitch_rect.GetCenter().x,
                             metrics.pitch_rect.GetCenter().y,
                             Metrics::MetersToPixels(9.15f), 0, 360, 200, thickness);

    //
    // arc north
    //
    GameLib::Primitives::Arc(window, metrics.pitch_rect.GetCenter().x,
                             metrics.pitch_rect.y + Metrics::YardsToPixels(18) - 100,
                             Metrics::MetersToPixels(9.15f), 30, 150, 100, thickness);

    //
    // arc south
    //
    GameLib::Primitives::Arc(window, metrics.pitch_rect.GetCenter().x,
                             metrics.pitch_rect.y + metrics.pitch_rect.h -
                                 Metrics::YardsToPixels(18) + 100,
                             Metrics::MetersToPixels(9.15f), 210, 330.5, 100, thickness);

    //
    // test draw goal line
    //
    GameLib::Primitives::OutlineColor(GameLib::Color(255, 0, 0, 255));
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.north_goal.x1, metrics.north_goal.y1),
        GameLib::Vector3(metrics.north_goal.x2, metrics.north_goal.y2), 4);
    GameLib::Primitives::DrawLine(
        window, GameLib::Vector3(metrics.south_goal.x1, metrics.south_goal.y1),
        GameLib::Vector3(metrics.south_goal.x2, metrics.south_goal.y2), 4);
}

void PitchTiled::InitMetrics(PitchMetrics m) {
    metrics = m;

    //    // perimiter lines
    //    lines.push_back(GameLib::Line(metrics.pitch_rect.x, metrics.pitch_rect.y,
    //                                  metrics.pitch_rect.x + metrics.pitch_rect.w,
    //                                  metrics.pitch_rect.y));
    //    lines.push_back(GameLib::Line(metrics.pitch_rect.x + metrics.pitch_rect.w,
    //                                  metrics.pitch_rect.y,
    //                                  metrics.pitch_rect.x + metrics.pitch_rect.w,
    //                                  metrics.pitch_rect.y + metrics.pitch_rect.h));
    //    lines.push_back(GameLib::Line(metrics.pitch_rect.x + metrics.pitch_rect.w,
    //                                  metrics.pitch_rect.y + metrics.pitch_rect.h,
    //                                  metrics.pitch_rect.x,
    //                                  metrics.pitch_rect.y + metrics.pitch_rect.h));
    //    lines.push_back(GameLib::Line(metrics.pitch_rect.x,
    //                                  metrics.pitch_rect.y + metrics.pitch_rect.h,
    //                                  metrics.pitch_rect.x,
    //                                  metrics.pitch_rect.y));
    //
    //    // center line
    //    lines.push_back(GameLib::Line(
    //                        metrics.pitch_rect.x, metrics.pitch_rect.y +
    //                        metrics.pitch_rect.h / 2,
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w,
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h / 2));
    //
    //    // north 18 yard box
    //    lines.push_back(GameLib::Line(
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                        Metrics::YardsToPixels(22),
    //                        metrics.pitch_rect.y, metrics.pitch_rect.x +
    //                        metrics.pitch_rect.w / 2 -
    //                        Metrics::YardsToPixels(22),
    //                        metrics.pitch_rect.y + Metrics::YardsToPixels(18)));
    //
    //    lines.push_back(
    //        GameLib::Line(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                      Metrics::YardsToPixels(22),
    //                      metrics.pitch_rect.y + Metrics::YardsToPixels(18),
    //                      metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                      Metrics::YardsToPixels(22),
    //                      metrics.pitch_rect.y + Metrics::YardsToPixels(18)));
    //
    //    lines.push_back(
    //        GameLib::Line(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                      Metrics::YardsToPixels(22),
    //                      metrics.pitch_rect.y + Metrics::YardsToPixels(18),
    //                      metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                      Metrics::YardsToPixels(22),
    //                      metrics.pitch_rect.y));
    //
    //    // north 6 yard box
    //    lines.push_back(
    //        GameLib::Line(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                      Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
    //                      metrics.pitch_rect.y,
    //                      metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                      Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
    //                      metrics.pitch_rect.y + Metrics::YardsToPixels(6)));
    //
    //    lines.push_back(
    //        GameLib::Line(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                      Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
    //                      metrics.pitch_rect.y + Metrics::YardsToPixels(6),
    //                      metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                      Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
    //                      metrics.pitch_rect.y + Metrics::YardsToPixels(6)));
    //
    //    lines.push_back(
    //        GameLib::Line(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                      Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
    //                      metrics.pitch_rect.y + Metrics::YardsToPixels(6),
    //                      metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                      Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
    //                      metrics.pitch_rect.y));
    //
    //    // south 18 yard box
    //    lines.push_back(
    //        GameLib::Line(metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                      Metrics::YardsToPixels(22),
    //                      metrics.pitch_rect.y + metrics.pitch_rect.h,
    //                      metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                      Metrics::YardsToPixels(22),
    //                      metrics.pitch_rect.y + metrics.pitch_rect.h -
    //                      Metrics::YardsToPixels(18)));
    //
    //    lines.push_back(GameLib::Line(
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                        Metrics::YardsToPixels(22),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h -
    //                        Metrics::YardsToPixels(18),
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                        Metrics::YardsToPixels(22),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h -
    //                        Metrics::YardsToPixels(18)));
    //
    //    lines.push_back(GameLib::Line(
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                        Metrics::YardsToPixels(22),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h -
    //                        Metrics::YardsToPixels(18),
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                        Metrics::YardsToPixels(22),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h));
    //
    //    // south 6 yard box
    //    lines.push_back(GameLib::Line(
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                        Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h,
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                        Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h -
    //                        Metrics::YardsToPixels(6)));
    //
    //    lines.push_back(GameLib::Line(
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 -
    //                        Metrics::YardsToPixels(22) + Metrics::YardsToPixels(12),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h -
    //                        Metrics::YardsToPixels(6),
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                        Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h -
    //                        Metrics::YardsToPixels(6)));
    //
    //    lines.push_back(GameLib::Line(
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                        Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h -
    //                        Metrics::YardsToPixels(6),
    //                        metrics.pitch_rect.x + metrics.pitch_rect.w / 2 +
    //                        Metrics::YardsToPixels(22) - Metrics::YardsToPixels(12),
    //                        metrics.pitch_rect.y + metrics.pitch_rect.h));
}

} // SenselessSoccer
