#pragma once

#include "../../metrics/metrics.h"
#include <map>

namespace SenselessSoccer {

class Role {
  public:
    explicit Role(const std::string &filename);
    int GetPosition(unsigned int ball_sector, Compass side);

  protected:
    std::map<int, int> south_positions;
    std::map<int, int> north_positions;
};
}
