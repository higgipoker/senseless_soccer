#include "game.h"

#include "../pitch/pitch.h"
#include <iostream>
namespace SenselessSoccer {

// ------------------------------------------------------------
// sort predicate for renderable objects (for height)
// ------------------------------------------------------------
struct {
    bool operator() (const GameLib::GameEntity *r1, const GameLib::GameEntity *r2) const {
        if (r1->renderable && r2->renderable) {
            return r1->renderable->z_order < r2->renderable->z_order;
        }
        return false;
    }
} sort_renderable;

// ------------------------------------------------------------
// SenselessGame
// ------------------------------------------------------------
SenselessGame::SenselessGame (const std::string &gamename, unsigned int x, unsigned int y, unsigned int w, unsigned int h, bool fullscreen)
    : GameLib::Game (gamename, x, y, w, h, fullscreen) {
}

// ------------------------------------------------------------
// render
// ------------------------------------------------------------
void SenselessGame::Render() {
    // clear
    window.Clear();

    // sort the render list in z-order
    std::sort (game_entities.begin(), game_entities.end(), sort_renderable);

    // set camera view
    window.SetView (camera.view);

    // render all game graphics
    for (auto it = game_entities.begin(); it != game_entities.end(); ++it) {
        (*it)->renderable->Render (window);
    }

    // non moving view for the hud
    render_hud();

    // flip buffers
    window.Present();
}

// ------------------------------------------------------------
// render_hud
// ------------------------------------------------------------
void SenselessGame::render_hud() {
    // hud view dimensions should match main camera view
    hud_view.setSize (camera.view.getSize());
    hud_view.setCenter (sf::Vector2f (hud_view.getSize().x / 2, hud_view.getSize().y / 2));

    // activate hud view for rendering
    window.SetView (hud_view);

    // render hud graphics
    for (auto it = hud_entities.begin(); it != hud_entities.end(); ++it) {
        (*it)->renderable->Render (window);
    }
}

// ------------------------------------------------------------
// handle_keyboard
// ------------------------------------------------------------
void SenselessGame::HandleInput() {
    // check inputs
    GameLib::WindowEvent event = window.PollEvent();

    switch (event.type) {
        case GameLib::WINDOW_EVENT_CLOSE:
            running = false;
            break;

        case GameLib::WINDOW_EVENT_MOUSE_CLICKED: {
            sf::Vector2i position = sf::Mouse::getPosition();
            on_mouse_click (position.x - window.GetPosition().x, position.y - window.GetPosition().y);
        }
        break;

        case GameLib::WINDOW_EVENT_KEY_DOWN:
            console.OnKey (event.param);
            break;

        case GameLib::WINDOW_EVENT_MOUSE_WHEEL_MOVED: {
            float z = std::stof (event.param);
            if (z > 0) {
                camera.ZoomIn();
            } else {
                camera.ZoomOut();
            }
            break;
        }

        case GameLib::WINDOW_EVENT_NONE:
        default:
            break;
    }
}

void SenselessGame::on_mouse_click (float x, float y) {

    // get the ball enity
    GameLib::GameEntity *b = GetEntity ("ball");

    // get the camera entity (TODO: util function to convert screen->world coordinates)
    GameLib::Camera *c = static_cast<GameLib::Camera *> (GetEntity ("camera"));

    if (b && c) {
        // put the ball there
        b->SetPosition (x + c->GetViewport().x, y + c->GetViewport().y, 100);
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
