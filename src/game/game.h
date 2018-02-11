/****************************************************************************
 * Copyright (c) 2018 P. Higgins
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 * 3. This notice may not be removed or altered from any source distribution.
 ****************************************************************************/
/**
 * @file game.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
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
    SenselessGame(const std::string &gamename, unsigned int x, unsigned int y,
                  unsigned int w, unsigned int h, bool fullscreen = false);

    /**
     * @brief ~SenselessGame
     */
    virtual ~SenselessGame() {}

  protected:
    /**
     * @brief keyboard handling
     */
    void handle_input(GameLib::WindowEvent &event) override;

    /**
     * @brief on_mouse_click
     * @param x
     * @param y
     */
    void on_mouse_click(float x, float y) override;
};

} // namespace SenselessSoccer
