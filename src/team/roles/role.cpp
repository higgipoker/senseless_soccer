#include "role.h"

#include <gamelib/files/file.h>

namespace SenselessSoccer {

Role::Role(const std::string &filename) {
    GameLib::File file(filename);
    std::vector<std::string> lines = file.GetLines("//");

    int i = 0;

    for (auto line : lines) {
        std::string str = line;
        std::size_t pos = str.find(":");
        std::string first = str.substr(0, pos);
        std::string second = str.substr(pos + 1);

        south_positions[i] = atoi(first.c_str());
        north_positions[i] = atoi(second.c_str());
        ++i;
    }
}

int Role::GetPosition(int ball_sector, Compass side) {
    if (south_positions.size()) {

        switch (side) {

            case SOUTH:
                return north_positions[ball_sector];

            case NORTH:
                return south_positions[ball_sector];

            case EAST:
            case WEST:
            case NORTH_EAST:
            case NORTH_WEST:
            case SOUTH_EAST:
            case SOUTH_WEST:
                break;
        }
    }

    return -1;
}
}
