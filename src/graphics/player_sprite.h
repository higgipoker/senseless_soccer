#pragma once

#include <map>
#include <gamelib/graphics/sprite.h>
#include <gamelib/graphics/primitives.h>
#include <gamelib/graphics/text.h>

namespace SenselessSoccer {

class PlayerSprite : public GameLib::Sprite {
public:
    explicit PlayerSprite(const std::string &filename, unsigned int number_rows, unsigned int number_cols);

    /**
     * @brief render
     */
    virtual void Render(GameLib::Window &window) override;

    void SetStandingAnimation(GameLib::Vector3 direction);
    void SetRunningAnimation(GameLib::Vector3 direction);
    void SetSlidingAnimation(GameLib::Vector3 direction);

    /// some shapes for debug rendering
    GameLib::Circle circle1;
    GameLib::Circle circle2;
    GameLib::Triangle triangle1;
    GameLib::Color triangle1_color;
    GameLib::Label text;

protected:

    /// to map animations to running directions
    std::map<int, std::string> running_animation_map;

    /// map for standing directions
    std::map<int, std::string> standing_animation_map;

    /// to map animations to sliding directions
    std::map<int, std::string> sliding_animation_map;

    /// track the last angle for standing anims
    float last_angle;
};

class PlayerShadowSprite : public PlayerSprite {
public:
    explicit PlayerShadowSprite(const std::string &filename, unsigned int number_rows, unsigned int number_cols)
    : PlayerSprite(filename, number_rows, number_cols){

    }
    /**
     * @brief render
     */
    virtual void Render(GameLib::Window &window) override;

protected:
};

}// SenselessSoccer

