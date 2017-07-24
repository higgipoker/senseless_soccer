#pragma once

#include <gamelib/gamelib.h>

namespace SenselessSoccer {

class BallSprite : public GameLib::Sprite {
public:
    explicit BallSprite(const std::string& filename, unsigned int number_rows, unsigned int number_cols);

    /**
     * \brief update animation
     */
    virtual void Animate() override;

    /**
     * \brief the ball sprite has special roll rotation
     * \param degrees self explanatory!
     */
    void SetRotation(int degrees);

    /**
    * \brief render
    */
    virtual void Render(GameLib::Window &window) override;

    /// some shapes for debug rendering
    GameLib::Circle circle1;

private:
};

class BallShadowSprite : public GameLib::Sprite {
public:
    explicit BallShadowSprite(const std::string& filename, unsigned int number_rows, unsigned int number_cols);

    /**
    * \brief render
    */
    virtual void Render(GameLib::Window &window) override;

    /// some shapes for debug rendering
    GameLib::Circle circle1;
protected:
};


}// SenselessSoccer


