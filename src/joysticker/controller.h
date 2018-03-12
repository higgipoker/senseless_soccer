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
 * @file controller.h
 * @author Paul Higgins <paul.samuel.higgins@gmail.com>
 * @date 2018
 * @brief description
 */
#pragma once
#include <gamelib/input/keyboard.h>
#include <set>
namespace SenselessSoccer {

/** @brief event ids */
enum ControllerEventID {
    NO_EVENT = 0,
    FIRE_PRESS,
    FIRE_RELEASE,
    FIRE_TAP,
    FIRE_DOUBLE_TAP
};

/**
 * @brief The ControllerEvent struct
 */
struct ControllerEvent {
    ControllerEvent() {
        id = NO_EVENT;
        param = 0;
    }

    /**
     * @brief ControllerEvent
     * @param i
     * @param p
     */
    ControllerEvent(ControllerEventID i, int p = 0) {
        id = i;
        param = p;
    }

    /// id
    ControllerEventID id;

    /// param
    int param;
};

/**
 * @brief The ControllerListener class
 */
class ControllerListener {
  public:
    /**
     * @brief ~ControllerListener
     */
    virtual ~ControllerListener();

    /**
    * @brief constructor
    * @param event event to handle
    */
    virtual void OnControllerEvent(ControllerEvent event) = 0;
};

/**
 * @brief The SensiController class
 */
class Controller : public GameLib::Keyboard {
  public:
    /**
     * @brief Update
     */
    virtual void Update() override;

    /**
     * @brief AddListener
     * @param listener listener to add
     */
    void AddListener(ControllerListener *listener);

    /**
     * @brief RemoveListener
     * @param listener listener to remove
     */
    void RemoveListener(ControllerListener *listener);

  protected:
    /**
     * @brief Notify
     * @param event event to handle
     */
    void Notify(ControllerEvent event);

    /// list of listeners
    std::set<ControllerListener *> listeners;

    /// release flag
    bool wait_for_release = false;
};

} // namespace SenselessSoccer
