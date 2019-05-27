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
 * @file player_state.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "player_state.h"
#include "../player.h"
#include "running.h"
#include "sliding.h"
#include "standing.h"

namespace SenselessSoccer {

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------
PlayerState::PlayerState(Player &p) : player(p), next_state(PLAYER_STATE_NONE) {}

// -----------------------------------------------------------------------------
// ChangeToNextState
// -----------------------------------------------------------------------------
void PlayerState::ChangeToNextState() {

    switch (next_state) {

        case PLAYER_STATE_STAND:
            player.ChangeState(new Standing(player));
            break;

        case PLAYER_STATE_RUN:
            player.ChangeState(new Running(player));
            break;

        case PLAYER_STATE_SLIDE:
            player.ChangeState(new Sliding(player));
            break;

        case PLAYER_STATE_NONE:
            break;
    }
}

// -----------------------------------------------------------------------------
// handle_input
// -----------------------------------------------------------------------------
void PlayerState::handle_input() {
    // poll for inputs
    player.input->Update();
}

// -----------------------------------------------------------------------------
// HandleEvent
// -----------------------------------------------------------------------------
bool PlayerState::HandleEvent(ControllerEvent event) {

    switch (event.id) {
        case FIRE:
            std::cout << "FIRE ";
            if (event.status == PRESSED) {
                std::cout << "PRESSED" << std::endl;
            } else {
                std::cout << "RELEASED" << std::endl;
                if (player.ball_under_control()) {
                    player.kick(event.param);
                    return true;
                }
            }
            break;

        case DPAD_LEFT:
            std::cout << "DPAD_LEFT ";
            if (event.status == PRESSED) {
                player.velocity.x = -1;
                std::cout << "PRESSED" << std::endl;
            } else {
                player.velocity.x = 0;
                std::cout << "RELEASED" << std::endl;
            }
            break;

        case DPAD_RIGHT:
            std::cout << "DPAD_RIGHT ";
            if (event.status == PRESSED) {
                player.velocity.x = 1;
                std::cout << "PRESSED" << std::endl;
            } else {
                player.velocity.x = 0;
                std::cout << "RELEASED" << std::endl;
            }
            break;

        case DPAD_UP:
            std::cout << "DPAD_UP ";
            if (event.status == PRESSED) {
                player.velocity.y = -1;
                std::cout << "PRESSED" << std::endl;
            } else {
                player.velocity.y = 0;
                std::cout << "RELEASED" << std::endl;
            }
            break;

        case DPAD_DOWN:
            std::cout << "DPAD_DOWN ";
            if (event.status == PRESSED) {
                player.velocity.y = 1;
                std::cout << "PRESSED" << std::endl;
            } else {
                std::cout << "RELEASED" << std::endl;
                player.velocity.y = 0;
            }
            break;

        case NO_EVENT:
            break;
    }

    return false;
}
} // SenselessSoccer
