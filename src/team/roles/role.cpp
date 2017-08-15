#include "role.h"

#include <gamelib/files/file.h>

namespace SenselessSoccer {

Role::Role(const std::string &filename) {
    GameLib::File file(filename);
    std::vector<std::string> lines = file.GetLines("//");

    unsigned int i = 0;

    for(auto it = lines.begin(); it != lines.end(); ++it) {
        std::string str = *it;
        std::size_t pos = str.find(":");
        std::string first = str.substr(0, pos);
        std::string second = str.substr(pos + 1);

        south_positions[i] = atoi(first.c_str());
        north_positions[i] = atoi(second.c_str());
        ++i;
    }
}

int Role::GetPosition(int ball_sector) {
    if(ball_sector >= 0 && ball_sector < south_positions.size()) {
        return south_positions[ball_sector];
    }

    return -1;
}
}
