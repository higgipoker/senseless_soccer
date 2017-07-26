#include "metrics.h"

namespace SenselessSoccer {

int Metrics::MetersToPixels(float meters) { return meters * 22; }

float Metrics::PixelsToMeters(float pixels) { return pixels / 22.0f; }

float Metrics::YardsToMeters(float yards) { return yards * 0.914f; }

int Metrics::YardsToPixels(float yards) {
  return MetersToPixels(YardsToMeters(yards));
}

Compass Metrics::VectorToCompass(const GameLib::Vector3 &v) {
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

GameLib::Vector3 Metrics::compasstoVector(const Compass &c) {
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
  }

  return v;
}

}  // SenselessSoccer
