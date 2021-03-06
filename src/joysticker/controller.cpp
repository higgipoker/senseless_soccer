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
#include <cassert>

namespace SenselessSoccer {

// -----------------------------------------------------------------------------
// ~ControllerListene
// -----------------------------------------------------------------------------
ControllerListener::~ControllerListener() = default;

Controller::Controller(GameLib::Input *i) { input = i; }

Controller::~Controller() = default;

// -----------------------------------------------------------------------------
// Update
// -----------------------------------------------------------------------------
void Controller::Update() {
  // for comparison for events (chaged statuses)
  int old_states[GameLib::TOTAL_EVENTS] = {
      input->event_states[0], input->event_states[1], input->event_states[2],
      input->event_states[3], input->event_states[4], input->event_states[5],
      input->event_states[6], input->event_states[7], input->event_states[8],
      input->event_states[9], input->event_states[10]};

  input->Update();

  //
  // FIRE
  //
  if (old_states[GameLib::FIRE_DOWN]) {
    if (input->event_states[GameLib::FIRE_UP]) {
      Notify(ControllerEvent(FIRE, RELEASED,
                             input->event_states[GameLib::FIRE_LENGTH_CACHED]));
    }

  } else {
    if (input->event_states[GameLib::FIRE_DOWN]) {
      Notify(ControllerEvent(FIRE, PRESSED));
    }
  }

  //
  // LEFT
  //
  if (!old_states[GameLib::LEFT]) {
    if (input->event_states[GameLib::LEFT]) {
      Notify(ControllerEvent(DPAD_LEFT, PRESSED));
    }
  } else {
    if (!input->event_states[GameLib::LEFT]) {
      Notify(ControllerEvent(DPAD_LEFT, RELEASED));
    }
  }

  //
  // RIGHT
  //
  if (!old_states[GameLib::RIGHT]) {
    if (input->event_states[GameLib::RIGHT]) {
      Notify(ControllerEvent(DPAD_RIGHT, PRESSED));
    }
  } else {
    if (!input->event_states[GameLib::RIGHT]) {
      Notify(ControllerEvent(DPAD_RIGHT, RELEASED));
    }
  }

  //
  // UP
  //
  if (!old_states[GameLib::UP]) {
    if (input->event_states[GameLib::UP]) {
      Notify(ControllerEvent(DPAD_UP, PRESSED));
    }
  } else {
    if (!input->event_states[GameLib::UP]) {
      Notify(ControllerEvent(DPAD_UP, RELEASED));
    }
  }

  //
  // DOWN
  //
  if (!old_states[GameLib::DOWN]) {
    if (input->event_states[GameLib::DOWN]) {
      Notify(ControllerEvent(DPAD_DOWN, PRESSED));
    }
  } else {
    if (!input->event_states[GameLib::DOWN]) {
      Notify(ControllerEvent(DPAD_DOWN, RELEASED));
    }
  }
}

// -----------------------------------------------------------------------------
// AddListener
// -----------------------------------------------------------------------------
void Controller::AddListener(SenselessSoccer::ControllerListener *listener) {
  listeners.insert(listener);
}

// -----------------------------------------------------------------------------
// RemoveListener
// -----------------------------------------------------------------------------
void Controller::RemoveListener(SenselessSoccer::ControllerListener *listener) {
  listeners.erase(listeners.find(listener));
}

// -----------------------------------------------------------------------------
// Notify
// -----------------------------------------------------------------------------
void Controller::Notify(ControllerEvent event) {
  for (auto listener : listeners) {
    listener->OnControllerEvent(event);
  }
}

} // namespace SenselessSoccer
