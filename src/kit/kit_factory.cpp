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
 * @file kit_factory.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "kit_factory.h"

namespace SenselessSoccer {

// shirt colours have 4 shades
static GameLib::Color original_brightest(255, 0, 0);
static GameLib::Color original_bright(215, 0, 0);
static GameLib::Color original_medium(175, 0, 0);
static GameLib::Color original_dark(135, 0, 0);

// shorts colours have 4 shades
static GameLib::Color shorts_original_brightest(255, 255, 255);
static GameLib::Color shorts_original_bright(215, 215, 215);
static GameLib::Color shorts_original_medium(175, 175, 175);
static GameLib::Color shorts_original_bdark(135, 135, 135);

// socks have 2 colors
static GameLib::Color socks_original_bright(0, 0, 255);
static GameLib::Color socks_original_dark(0, 0, 215);

// blue colors
static GameLib::Color blue_brightest(0, 0, 255);
static GameLib::Color blue_bright(0, 0, 215);
static GameLib::Color blue_medium(0, 0, 175);
static GameLib::Color blue_dark(0, 0, 135);

// black colors
static GameLib::Color black_brightest(80, 80, 80);
static GameLib::Color black_bright(60, 60, 60);
static GameLib::Color black_medium(30, 30, 30);
static GameLib::Color black_dark(0, 0, 0);

// white colors
static GameLib::Color white_brightest(255, 255, 255);
static GameLib::Color white_bright(215, 215, 215);
static GameLib::Color white_medium(175, 175, 175);
static GameLib::Color white_dark(135, 135, 135);

// green colors
static GameLib::Color green_brightest(0, 255, 0);
static GameLib::Color green_bright(0, 215, 0);
static GameLib::Color green_medium(0, 175, 0);
static GameLib::Color green_dark(0, 135, 0);

// -----------------------------------------------------------------------------
// GetDefaultRedKit
// -----------------------------------------------------------------------------
std::vector<std::pair<GameLib::Color, GameLib::Color>>
KitFactory::GetDefaultRedKit() {
    // default kit is already red shirts

    std::vector<std::pair<GameLib::Color, GameLib::Color>> p;
    //
    // SHORTS
    //
    //    p.push_back(std::make_pair(shorts_original_brightest,
    //    original_brightest));
    //    p.push_back(std::make_pair(shorts_original_bright, original_bright));
    //    p.push_back(std::make_pair(shorts_original_medium, original_medium));
    //    p.push_back(std::make_pair(shorts_original_bdark, original_dark));

    //
    // SOCKS
    //
    p.emplace_back(socks_original_bright, original_brightest);
    p.emplace_back(socks_original_dark, original_bright);
    return p;
}

// -----------------------------------------------------------------------------
// GetDefaultBlueKit
// -----------------------------------------------------------------------------
std::vector<std::pair<GameLib::Color, GameLib::Color>>
KitFactory::GetDefaultBlueKit() {

    std::vector<std::pair<GameLib::Color, GameLib::Color>> p;

    //
    // SHIRT
    //
    p.emplace_back(original_brightest, blue_brightest);
    p.emplace_back(original_bright, blue_bright);
    p.emplace_back(original_medium, blue_medium);
    p.emplace_back(original_dark, blue_dark);

    //
    // SHORTS
    //
    //    p.push_back(std::make_pair(shorts_original_brightest,
    //    blue_brightest));
    //    p.push_back(std::make_pair(shorts_original_bright, blue_bright));
    //    p.push_back(std::make_pair(shorts_original_medium, blue_medium));
    //    p.push_back(std::make_pair(shorts_original_bdark, blue_dark));
    return p;
}

// -----------------------------------------------------------------------------
// GetKeeperPalette
// -----------------------------------------------------------------------------
std::vector<std::pair<GameLib::Color, GameLib::Color>>
KitFactory::GetKeeperPalette() {
    std::vector<std::pair<GameLib::Color, GameLib::Color>> p;
    p.emplace_back(original_brightest, green_brightest);
    p.emplace_back(original_bright, green_bright);
    p.emplace_back(original_medium, green_medium);
    p.emplace_back(original_dark, green_dark);
    return p;
}

} // namespace
