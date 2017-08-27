#include "game.h"

#include "../pitch/pitch.h"
#include <iostream>
namespace SenselessSoccer {

SenselessGame::SenselessGame(const std::string &gamename, int x, int y, int w, int h, bool fullscreen)
    : GameLib::Game(gamename, x, y, w, h, fullscreen) {
}

void SenselessGame::on_mouse_click(int x, int y) {

    // get the ball enity
    GameLib::GameEntity *b = GetEntity("ball");

    // get the camera entity (TODO: util function to convert screen->world coordinates)
    GameLib::Camera *c = (GameLib::Camera *)GetEntity("camera");

    if(b && c) {
        // put the ball there
        b->SetPosition(x + c->GetViewport().x, y + c->GetViewport().y, 5);
        b->physical->ResetVelocity();
    }
}

}// namespace SenselessSoccer
