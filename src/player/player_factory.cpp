/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file player_factory.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "player_factory.h"
namespace SenselessSoccer {

std::vector<Player *> PlayerFactory::players;
std::vector<GameLib::Sprite *> PlayerFactory::sprites;
std::vector<GameLib::Physical *> PlayerFactory::physicals;
std::vector<Role *> PlayerFactory::roles;

const static std::string FILENAME = "gfx/player/player.png";
const static std::string FILENAME_SHADOW = "gfx/player/player_shadow.png";

// -----------------------------------------------------------------------------
// MakePlayer
// -----------------------------------------------------------------------------
Player *PlayerFactory::MakePlayer(const std::string &entityname, const std::string &role_filename) {

    // things that a player needs
    GameLib::Physical *physical = new GameLib::Physical;
    PlayerSprite *player_sprite = new PlayerSprite(FILENAME, 6, 24);
    PlayerShadowSprite *shadow_sprite = new PlayerShadowSprite(FILENAME_SHADOW, 6, 24);
    player_sprite->shadow = shadow_sprite;
    Role *role = new Role("data/" + role_filename);

    // set up the player
    Player *player = new Player(physical, player_sprite);
    player->SetName(entityname);
    player->SetPosition(100, 100);
    player->role = role;

    // save for freeing memory later
    players.push_back(player);
    sprites.push_back(player_sprite);
    sprites.push_back(shadow_sprite);
    physicals.push_back(physical);
    roles.push_back(role);

    // return the pointer
    return player;
}

// -----------------------------------------------------------------------------
// destruct
// -----------------------------------------------------------------------------
PlayerFactory::~PlayerFactory() {
    for (auto role : roles) {
        delete role;
    }
    for (auto physical : physicals) {
        delete physical;
    }
    for (auto sprite : sprites) {
        delete sprite;
    }
    for (auto player : players) {
        delete player;
    }
}

} // namespace SenselessSoccer
