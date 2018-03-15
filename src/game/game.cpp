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
 * @file game.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "game.h"

#include "../pitch/pitch.h"
#include <iostream>
namespace SenselessSoccer {

// ------------------------------------------------------------
// sort predicate for renderable objects (for height)
// ------------------------------------------------------------
struct {
  bool operator()(const GameLib::GameEntity *r1,
                  const GameLib::GameEntity *r2) const {
    return r1->renderable.z_order < r2->renderable.z_order;
  }
} sort_renderable;

// ------------------------------------------------------------
// SenselessGame
// ------------------------------------------------------------
SenselessGame::SenselessGame(const std::string &gamename, unsigned int x,
                             unsigned int y, unsigned int w, unsigned int h,
                             bool fullscreen)
  : GameLib::Game(gamename, x, y, w, h, fullscreen) {
  window.SetIcon("gfx/icon.png");
}

// ------------------------------------------------------------
// HandleInput
// ------------------------------------------------------------
void SenselessGame::handle_input(GameLib::WindowEvent &event) {
  GameLib::Game::handle_input(event);
  // do game specific handling here
}

// ------------------------------------------------------------
// on_mouse_click
// ------------------------------------------------------------
void SenselessGame::on_mouse_click(float x, float y) {
  // get the ball enity
  GameLib::GameEntity ball = GetEntity("ball");

  // put the ball there
  ball.SetPosition(x + camera.GetViewport().x, y + camera.GetViewport().y, 300);
  ball.physical.ResetVelocity();
}
} // namespace SenselessSoccer
