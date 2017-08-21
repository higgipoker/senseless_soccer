#include "ball_sprite.h"

#include <gamelib/graphics/primitives.h>

namespace SenselessSoccer {

BallSprite::BallSprite(const std::string &filename, unsigned int number_rows, unsigned int number_cols) : GameLib::Sprite(filename, number_rows, number_cols) {

    z_order = 10;

    std::vector<int> roll;

    roll.push_back(0);
    roll.push_back(1);
    roll.push_back(2);
    roll.push_back(3);
    roll.push_back(4);
    roll.push_back(5);
    roll.push_back(6);

    AddAnimation("roll", 50, true, roll);
    SetAnimation("roll");
    SetFrame(0);
}

void BallSprite::Animate() {
    GameLib::Sprite::Animate();
}

void BallSprite::SetRotation(int degrees) {
    sprite.setRotation(degrees);
}

void BallSprite::Render(GameLib::Window &window) {
    GameLib::Sprite::Render(window);

#ifdef RENDER_DEBUG

    if(circle1.radius) {
        GameLib::Primitives::Circle(window, circle1.x, circle1.y, circle1.radius);
    }

#endif
}

BallShadowSprite::BallShadowSprite(const std::string &filename, unsigned int number_rows, unsigned int number_cols)
    : GameLib::Sprite(filename, number_rows, number_cols) {
    z_order = 0;
    SetFrame(0);
}

void BallShadowSprite::Render(GameLib::Window &window) {
    GameLib::Sprite::Render(window);

#ifdef RENDER_DEBUG

    if(circle1.radius) {
        GameLib::Primitives::Circle(window, circle1.x, circle1.y, circle1.radius);
    }

#endif
}

} // SenselessSoccer
