#pragma once

#include <gamelib/game/game.h>
#include "../pitch/pitch.h"
#include "../ball/ball.h"

namespace SenselessSoccer {
class SenselessGame : public GameLib::Game {
public:
    /**
     * \brief construct
     * \param gamename string name
     * \param x window x location
     * \param y window y location
     * \param w window width
     * \param h window height
     * \fullscreen full screen window or now
     */
    SenselessGame(const std::string &gamename, int x, int y, int w, int h, bool fullscreen);

    /// a pitch
    Pitch *pitch;

    /// a ball
    Ball *ball;

protected:
    virtual void on_mouse_click(int x, int y) override;
};
}
