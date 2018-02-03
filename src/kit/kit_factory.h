#pragma once
#include <SFML/Graphics.hpp>
#include <gamelib/graphics/color.h>
#include <vector>

namespace SenselessSoccer {

/**
*@brief The KitFactory class
*/
class KitFactory {
public:
    /**
    * @brief GetDefaultRedKit
    * @return
    */
    static std::vector<std::pair<sf::Color, sf::Color>> GetDefaultRedKit();

    /**
     * @brief GetDefaultBlueKit
     * @return
     */
    static std::vector<std::pair<sf::Color, sf::Color>> GetDefaultBlueKit();

    /**
     * @brief GetKeeperPalette
     * @return
     */
    static std::vector<std::pair<sf::Color, sf::Color>> GetKeeperPalette();

private:
};
}
