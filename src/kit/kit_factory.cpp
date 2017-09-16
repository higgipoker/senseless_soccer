#include "kit_factory.h"

namespace SenselessSoccer {

// shirt colours have 4 shades
static sf::Color original_brightest(255, 0, 0);
static sf::Color original_bright(215, 0, 0);
static sf::Color original_medium(175, 0, 0);
static sf::Color original_dark(135, 0, 0);

// shorts colours have 4 shades
static sf::Color shorts_original_brightest(255, 255, 255);
static sf::Color shorts_original_bright(215, 215, 215);
static sf::Color shorts_original_medium(175, 175, 175);
static sf::Color shorts_original_bdark(135, 135, 135);

// socks have 2 colors
static sf::Color socks_original_bright(0, 0, 255);
static sf::Color socks_original_dark(0, 0, 215);

// blue colors
static sf::Color blue_brightest(0, 0, 255);
static sf::Color blue_bright(0, 0, 215);
static sf::Color blue_medium(0, 0, 175);
static sf::Color blue_dark(0, 0, 135);

// black colors
static sf::Color black_brightest(80, 80, 80);
static sf::Color black_bright(60, 60, 60);
static sf::Color black_medium(30, 30, 30);
static sf::Color black_dark(0, 0, 0);

// white colors
static sf::Color white_brightest(255, 255, 255);
static sf::Color white_bright(215, 215, 215);
static sf::Color white_medium(175, 175, 175);
static sf::Color white_dark(135, 135, 135);

// green colors
static sf::Color green_brightest(0, 255, 0);
static sf::Color green_bright(0, 215, 0);
static sf::Color green_medium(0, 175, 0);
static sf::Color green_dark(0, 135, 0);

// ------------------------------------------------------------
// GetDefaultRedKit
// ------------------------------------------------------------
std::vector<std::pair<sf::Color, sf::Color>> KitFactory::GetDefaultRedKit() {
    // default kit is already red shirts

    std::vector<std::pair<sf::Color, sf::Color>> p;
    //
    // SHORTS
    //
    //    p.push_back(std::make_pair(shorts_original_brightest, original_brightest));
    //    p.push_back(std::make_pair(shorts_original_bright, original_bright));
    //    p.push_back(std::make_pair(shorts_original_medium, original_medium));
    //    p.push_back(std::make_pair(shorts_original_bdark, original_dark));

    //
    // SOCKS
    //
    p.push_back(std::make_pair(socks_original_bright, original_brightest));
    p.push_back(std::make_pair(socks_original_dark, original_bright));
    return p;
}

// ------------------------------------------------------------
// GetDefaultBlueKit
// ------------------------------------------------------------
std::vector<std::pair<sf::Color, sf::Color>> KitFactory::GetDefaultBlueKit() {

    std::vector<std::pair<sf::Color, sf::Color>> p;

    //
    // SHIRT
    //
    p.push_back(std::make_pair(original_brightest, blue_brightest));
    p.push_back(std::make_pair(original_bright, blue_bright));
    p.push_back(std::make_pair(original_medium, blue_medium));
    p.push_back(std::make_pair(original_dark, blue_dark));

    //
    // SHORTS
    //
    //    p.push_back(std::make_pair(shorts_original_brightest, blue_brightest));
    //    p.push_back(std::make_pair(shorts_original_bright, blue_bright));
    //    p.push_back(std::make_pair(shorts_original_medium, blue_medium));
    //    p.push_back(std::make_pair(shorts_original_bdark, blue_dark));
    return p;
}

// ------------------------------------------------------------
// GetKeeperPalette
// ------------------------------------------------------------
std::vector<std::pair<sf::Color, sf::Color>> KitFactory::GetKeeperPalette() {
    std::vector<std::pair<sf::Color, sf::Color>> p;
    p.push_back(std::make_pair(original_brightest, green_brightest));
    p.push_back(std::make_pair(original_bright, green_bright));
    p.push_back(std::make_pair(original_medium, green_medium));
    p.push_back(std::make_pair(original_dark, green_dark));
    return p;
}

} // namespace
