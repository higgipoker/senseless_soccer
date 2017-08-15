#pragma once

#include <gamelib/math/vector3.h>
#include <gamelib/math/shapes.h>

namespace SenselessSoccer {

/** @brief 8 directional */
enum Compass {
    NORTH = 0, NORTH_EAST, EAST, SOUTH_EAST, SOUTH, SOUTH_WEST, WEST, NORTH_WEST
};

/** @brief describe a pitch
 */
class PitchMetrics {

public:
    /**
     * @brief init pitch metrics
     * @param x x
     * @param y y
     * @param w width
     * @param h height
     */
    void Init(int x, int y, int w, int h) {
        pitch_rect.x = x;
        pitch_rect.y = y;
        pitch_rect.w = w;
        pitch_rect.h = h;
        inited = true;
    }

    /// has been initialised
    bool inited = false;

    /// pitch boundary
    GameLib::Rectangle pitch_rect;
private:
};

class Metrics {
public:

    /**
     * @brief converts meters to pixels
     * @param meters meters to convert
     */
    static int MetersToPixels(float meters);

    /**
     * @brief converts pixels to meters
     * @param pixels pixels to convert
     */
    static float PixelsToMeters(float pixels);

    /**
     * @brief converts yards to meters
     * @param yards yards to convert
     */
    static float YardsToMeters(float yards);

    /**
     * @brief converts yards to pixels
     * @param yards yards to convert
     */
    static int YardsToPixels(float yards);

    /**
     * @brief converts vector to compass
     * @param v vector to convert
     */
    static Compass VectorToCompass(const GameLib::Vector3 &v);

    /**
     * @brief converts compass to vector
     * @param c compassto convert
     */
    static GameLib::Vector3 compasstoVector(const Compass &c);
};

}// SenselessSoccer
