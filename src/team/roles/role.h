#pragma once

#include <map>

namespace SenselessSoccer {

class Role {
public:

    Role(const std::string &filename);
    int GetPosition(int ball_sector);

protected:
    std::map<int, int> south_positions;
    std::map<int, int> north_positions;
};

}
