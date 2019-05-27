#include "metrics.h"

namespace SenselessSoccer {

static const float cm_to_px = 0.2f;

// -----------------------------------------------------------------------------
// AngularWidth
// -----------------------------------------------------------------------------
float Metrics::AngularWidth(float actual_width, float screen_width, float camera_height){
    float angular_width = 0;

    // if the screen width is 800, then 1 degree is 4.44 pixels
//    float angular_pixel = 4.4444;

//    float z_position = physical.position.z;
//    float ball_diameter_at_zero = radius * 2;
//    float ball_diameter = 2.6;
//    float camera_height = 100;
//    float dist_from_camera = camera_height - physical.position.z;
//    float angular_diameter = 2 * (atanf(actual_width / (2 * dist_from_camera)));
//    float degs = DEGREES(angular_diameter);
//    float angular_pixels = degs * angular_pixel;

    return angular_width;
}

// -----------------------------------------------------------------------------
// MetersToPixels
// -----------------------------------------------------------------------------
int Metrics::MetersToPixels (float meters) {
    return meters * 100 * cm_to_px;
}

// -----------------------------------------------------------------------------
// PixelsToMeters
// -----------------------------------------------------------------------------
float Metrics::PixelsToMeters (float pixels) {
    return pixels / cm_to_px / 100;
}

// -----------------------------------------------------------------------------
// YardsToMeters
// -----------------------------------------------------------------------------
float Metrics::YardsToMeters (float yards) {
    return yards * 0.914f;
}

// -----------------------------------------------------------------------------
// YardsToPixels
// -----------------------------------------------------------------------------
int Metrics::YardsToPixels (float yards) {
    return MetersToPixels (YardsToMeters (yards));
}

// -----------------------------------------------------------------------------
// VectorToCompass
// -----------------------------------------------------------------------------
Compass Metrics::VectorToCompass (const GameLib::Vector3 &v) {
    Compass c = NORTH;

    if (v.x == 0 && v.y == -1)
        c = NORTH;

    else if (v.x == 1 && v.y == -1)
        c = NORTH_EAST;

    else if (v.x == 1 && v.y == 0)
        c = EAST;

    else if (v.x == 1 && v.y == 1)
        c = SOUTH_EAST;

    else if (v.x == 0 && v.y == 1)
        c = SOUTH;

    else if (v.x == -1 && v.y == 1)
        c = SOUTH_WEST;

    else if (v.x == -1 && v.y == 0)
        c = WEST;

    else if (v.x == -1 && v.y == -1)
        c = NORTH_WEST;

    return c;
}

// -----------------------------------------------------------------------------
// compasstoVector
// -----------------------------------------------------------------------------
GameLib::Vector3 Metrics::compasstoVector (const Compass &c) {
    GameLib::Vector3 v;

    switch (c) {
        case NORTH:
            v.x = 0;
            v.y = -1;
            break;

        case NORTH_EAST:
            v.x = 1;
            v.y = -1;
            break;

        case EAST:
            v.x = 1;
            v.y = 0;
            break;

        case SOUTH_EAST:
            v.x = 1;
            v.y = 1;
            break;

        case SOUTH:
            v.x = 0;
            v.y = 1;
            break;

        case SOUTH_WEST:
            v.x = -1;
            v.y = 1;
            break;

        case WEST:
            v.x = -1;
            v.y = 0;
            break;

        case NORTH_WEST:
            v.x = -1;
            v.y = -1;
            break;

        default:
            v.x = 0;
            v.y = 0;
            break;
    }

    return v;
}

}  // SenselessSoccer
