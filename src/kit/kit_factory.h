#pragma once
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
    static std::vector<std::pair<GameLib::Color, GameLib::Color>>
    GetDefaultRedKit();

    /**
     * @brief GetDefaultBlueKit
     * @return
     */
    static std::vector<std::pair<GameLib::Color, GameLib::Color>>
    GetDefaultBlueKit();

    /**
     * @brief GetKeeperPalette
     * @return
     */
    static std::vector<std::pair<GameLib::Color, GameLib::Color>>
    GetKeeperPalette();

  private:
};
}
