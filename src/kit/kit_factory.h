#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <gamelib/graphics/color.h>

namespace SenselessSoccer {

class KitFactory {
public:
    static std::vector<std::pair<sf::Color, sf::Color> > GetDefaultRedKit();
    static std::vector<std::pair<sf::Color, sf::Color> > GetDefaultBlueKit();
    static std::vector<std::pair<sf::Color, sf::Color> > GetKeeperPalette();
private:

};
}
