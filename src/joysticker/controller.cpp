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
 * @file controller.cpp
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#include "controller.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// ~ControllerListene
// ------------------------------------------------------------
ControllerListener::~ControllerListener() {}

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Controller::Update() {
    // to track if fire down has changed, save state before base update
    int prev_fire_state = event_states[GameLib::FIRE_DOWN];

    GameLib::Keyboard::Update();

    if (prev_fire_state) {
        if (event_states[GameLib::FIRE_UP]) {
            Notify(
                ControllerEvent(FIRE_RELEASE, event_states[GameLib::FIRE_LENGTH_CACHED]));
        }

    } else {
        if (event_states[GameLib::FIRE_DOWN]) {
            Notify(ControllerEvent(FIRE_PRESS));
        }
    }
}

// ------------------------------------------------------------
// AddListener
// ------------------------------------------------------------
void Controller::AddListener(SenselessSoccer::ControllerListener *listener) {
    listeners.insert(listener);
}

// ------------------------------------------------------------
// RemoveListener
// ------------------------------------------------------------
void Controller::RemoveListener(SenselessSoccer::ControllerListener *listener) {
    listeners.erase(listeners.find(listener));
}

// ------------------------------------------------------------
// Notify
// ------------------------------------------------------------
void Controller::Notify(ControllerEvent event) {
    for (auto it = listeners.begin(); it != listeners.end(); ++it) {
        (*it)->OnControllerEvent(event);
    }
}

} // namespace SenselessSoccer
