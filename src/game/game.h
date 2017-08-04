#pragma once

#include <gamelib/game/game.h>

namespace SenselessSoccer {
class SenselessGame : public GameLib::Game {
  public:
    SenselessGame(const std::string &gamename, int x, int y, int w, int h, bool fullscreen);

  protected:
    virtual void on_mouse_click(int x, int y) override;
};
}
