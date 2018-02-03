#pragma once

#include "../ball/ball.h"
#include "../pitch/pitch.h"
#include <gamelib/game/game.h>

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
     * \brief fullscreen full screen window or now
     */
    SenselessGame (const std::string &gamename, unsigned int x, unsigned int y, unsigned int w, unsigned int h, bool fullscreen);

    /**
     * @brief do rendering
     */
    void Render();

    /**
     * @brief keyboard handling
     */
    void HandleInput();

    /**
     * @brief calc_fps
     */
    void CalculateFPS();

protected:
    /**
     * @brief helper to render the hud
     */
    void render_hud();

    /**
     * @brief on_mouse_click
     * @param x
     * @param y
     */
    virtual void on_mouse_click (float x, float y) override;
};
}
