#pragma once

#include "player.h"

namespace SenselessSoccer {

class PlayerFactory {
public:
    ~PlayerFactory();
    Player *MakePlayer(const std::string &entityname, const std::string &role_filename);

private:
    std::vector<Player *> players;
};
}
