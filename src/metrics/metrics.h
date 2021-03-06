#pragma once

#include <gamelib/math/shapes.h>
#include <gamelib/math/vector3.h>

namespace SenselessSoccer {

/** @brief 8 directional */
enum Compass {
  NORTH = 0,
  NORTH_EAST,
  EAST,
  SOUTH_EAST,
  SOUTH,
  SOUTH_WEST,
  WEST,
  NORTH_WEST
};

class Metrics {
 public:
  /**
   * @brief AngularWidth
   * @param camera_height
   * @return
   */
  static float AngularWidth(float actual_width, float screen_width, float camera_height);

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

  /// trial and error force to pass ball one meter
  static constexpr float force_per_meter = 0.1f;
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

    // stuff we can calc from params
    int goal_width = Metrics::MetersToPixels(7.32);
    north_goal.x1 = pitch_rect.x + pitch_rect.w / 2 - goal_width / 2;
    north_goal.x2 = north_goal.x1 + goal_width;
    north_goal.y1 = north_goal.y2 = pitch_rect.y;

    south_goal = north_goal;
    south_goal.y1 += pitch_rect.h;
    south_goal.y2 += pitch_rect.h;

    inited = true;
  }

  /// has been initialised
  bool inited = false;

  /// pitch boundary
  GameLib::Rectangle pitch_rect;

  /// north goal
  GameLib::Line north_goal;

  /// south goal
  GameLib::Line south_goal;

 private:
};

}  // namespace SenselessSoccer
