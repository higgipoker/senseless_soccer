#pragma once

#include <gamelib/gamelib.h>

#include <map>

namespace SenselessSoccer {

class PlayerSprite : public GameLib::Sprite {
public:
    explicit PlayerSprite(const std::string& filename, unsigned int number_rows, unsigned int number_cols);

    /**
     * \brief update the running animation depending on direction
     * \param vel velocity
     * \param angle angle in the case that vel is zero
     */
    void UpdateAnimation(GameLib::Vector3 &vel, float angle);

    /**
     * \brief render
     */
    virtual void Render(GameLib::Window &window) override;

    /// some shapes for debug rendering
    GameLib::Circle circle1;
	GameLib::Circle circle2;

private:

    /// to map animations to running directions
    std::map<int, std::string> movement_animation_map;

    /// map for standing directions
    std::map<int, std::string> standing_animation_map;

    /// track the last angle for standing anims
    float last_angle;
};

}// SenselessSoccer

