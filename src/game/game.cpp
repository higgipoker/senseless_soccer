#include "game.h"

#include "../pitch/pitch.h"
#include <iostream>
namespace SenselessSoccer {

// ------------------------------------------------------------
// sort predicate for renderable objects (for height)
// ------------------------------------------------------------
struct {
    bool operator()(const GameLib::GameEntity *r1, const GameLib::GameEntity *r2) const {
        if (r1->renderable && r2->renderable) {
            return r1->renderable->z_order < r2->renderable->z_order;
        }
        return false;
    }
} sort_renderable;

// ------------------------------------------------------------
// SenselessGame
// ------------------------------------------------------------
SenselessGame::SenselessGame(const std::string &gamename, unsigned int x, unsigned int y, unsigned int w, unsigned int h, bool fullscreen)
    : GameLib::Game(gamename, x, y, w, h, fullscreen) {
    window.SetIcon("gfx/icon.png");
}

// ------------------------------------------------------------
// HandleInput
// ------------------------------------------------------------
void SenselessGame::HandleInput(GameLib::WindowEvent &event) {
    GameLib::Game::HandleInput(event);
    // do game specific handling here
}

// ------------------------------------------------------------
// on_mouse_click
// ------------------------------------------------------------
void SenselessGame::on_mouse_click(float x, float y) {

    // get the ball enity
    GameLib::GameEntity *b = GetEntity("ball");

    // get the camera entity (TODO: util function to convert screen->world coordinates)
    GameLib::Camera *c = static_cast<GameLib::Camera *>(GetEntity("camera"));

    if (b && c) {
        // put the ball there
        b->SetPosition(x + c->GetViewport().x, y + c->GetViewport().y, 300);
        b->physical->ResetVelocity();
    }
}

// ------------------------------------------------------------
// calc_fps
// ------------------------------------------------------------
void SenselessGame::CalculateFPS() {
    float currentTime = fps_clock.getElapsedTime().asSeconds();
    fps = 1.f / (currentTime - lastTime);
    lastTime = currentTime;
}
} // namespace SenselessSoccer
