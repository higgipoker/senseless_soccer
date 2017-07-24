#include "pitch_renderable.h"

#include <iostream>
#include <gamelib/math/shapes.h>
#include <gamelib/graphics/primitives.h>

namespace SenselessSoccer {

PitchTiled::PitchTiled (const std::string &filename, GameLib::Camera &c) :
	GameLib::Tileset (filename, c) {
	z_order = 1;
}

void PitchTiled::Render (GameLib::Window &window) {
	if (!metrics.inited) return;

	GameLib::Tileset::Render (window);

	// white lines
	GameLib::Primitives::outline_color.r = 255;
	GameLib::Primitives::outline_color.g = 255;
	GameLib::Primitives::outline_color.b = 255;
	GameLib::Primitives::outline_color.a = 50;

	int thickness = 10;
	// straight lines (configed list in InitMetrics)
	GameLib::Primitives::Lines (window, lines, thickness);

	// center circle
	GameLib::Primitives::Arc (window, metrics.pitch_rect.GetCenter().x, metrics.pitch_rect.GetCenter().y, Metrics::MetersToPixels (9.15f), 0, 360, 200, thickness);

	// arc north
	GameLib::Primitives::Arc (window, metrics.pitch_rect.GetCenter().x, metrics.pitch_rect.y + Metrics::YardsToPixels (18) - 100, Metrics::MetersToPixels (9.15f), 30, 150, 100, thickness);

	// arc south
	GameLib::Primitives::Arc (window, metrics.pitch_rect.GetCenter().x, metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (18) + 100, Metrics::MetersToPixels (9.15f), 210, 330, 100, thickness);
}

void PitchTiled::InitMetrics (PitchMetrics m) {
	metrics = m;

	// perimiter lines
	lines.push_back (GameLib::Line (metrics.pitch_rect.x, metrics.pitch_rect.y, metrics.pitch_rect.x + metrics.pitch_rect.w, metrics.pitch_rect.y));
	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w, metrics.pitch_rect.y, metrics.pitch_rect.x + metrics.pitch_rect.w, metrics.pitch_rect.y + metrics.pitch_rect.h));
	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w, metrics.pitch_rect.y + metrics.pitch_rect.h, metrics.pitch_rect.x, metrics.pitch_rect.y + metrics.pitch_rect.h));
	lines.push_back (GameLib::Line (metrics.pitch_rect.x, metrics.pitch_rect.y + metrics.pitch_rect.h, metrics.pitch_rect.x, metrics.pitch_rect.y));

	// center line
	lines.push_back (GameLib::Line (metrics.pitch_rect.x, metrics.pitch_rect.y + metrics.pitch_rect.h / 2, metrics.pitch_rect.x + metrics.pitch_rect.w, metrics.pitch_rect.y + metrics.pitch_rect.h / 2));

	// north 18 yard box
	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y,
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + Metrics::YardsToPixels (18))
	                );

	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + Metrics::YardsToPixels (18),
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + Metrics::YardsToPixels (18))
	                );

	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + Metrics::YardsToPixels (18),
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y)
	                );

	// north 6 yard box
	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22) + Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y,
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22) + Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + Metrics::YardsToPixels (6))
	                );

	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22) + Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + Metrics::YardsToPixels (6),
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22) - Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + Metrics::YardsToPixels (6))
	                );

	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22) - Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + Metrics::YardsToPixels (6),
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22) - Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y)
	                );

	// south 18 yard box
	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h,
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (18))
	                );

	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (18),
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (18))
	                );

	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (18),
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h)
	                );

	// south 6 yard box
	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22) + Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h,
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22) + Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (6))
	                );

	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 - Metrics::YardsToPixels (22) + Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (6),
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22) - Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (6))
	                );

	lines.push_back (GameLib::Line (metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22) - Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h - Metrics::YardsToPixels (6),
	                                metrics.pitch_rect.x + metrics.pitch_rect.w / 2 + Metrics::YardsToPixels (22) - Metrics::YardsToPixels (12),
	                                metrics.pitch_rect.y + metrics.pitch_rect.h)
	                );

}

}// SenselessSoccer
