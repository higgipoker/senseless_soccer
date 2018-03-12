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
 * @file player_factory.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once

#include "player.h"

namespace SenselessSoccer {

/**
 * @brief The PlayerFactory class
 */
class PlayerFactory {
  public:
    /**
     * @brief MakePlayer
     * @param entityname
     * @param role_filename
     * @return
     */
    static Player *MakePlayer(const std::string &entityname, const std::string &role_filename);

    /**
     * @brief Destroy
     */
    static void Destroy();

  private:
    /// to save for cleaning up
    static std::vector<Player *> players;
    static std::vector<GameLib::Sprite *> sprites;
    static std::vector<GameLib::Physical *> physicals;
    static std::vector<Role *> roles;
};
} // namespace SenselessSoccer
