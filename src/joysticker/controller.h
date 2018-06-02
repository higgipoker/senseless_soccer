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

/**
 * @brief The ControllerEventID enum
 */
enum ControllerEventID {
    NO_EVENT = 0,
    FIRE,
    DPAD_LEFT,
    DPAD_RIGHT,
    DPAD_UP,
    DPAD_DOWN
};

/**
 * @brief The ControllerEventStatus enum
 */
enum ControllerEventStatus { RELEASED = 0, PRESSED };

/**
 * @brief The ControllerEvent struct
 */
struct ControllerEvent {
    ControllerEvent() {
        id = NO_EVENT;
        status = RELEASED;
        param = 0;
    }

    /**
     * @brief ControllerEvent
     * @param i
     * @param p
     */
    ControllerEvent(ControllerEventID i, ControllerEventStatus s, int p = 0) {
        id = i;
        status = s;
        param = p;
    }

    /// id
    ControllerEventID id;

    /// status
    ControllerEventStatus status;

    /// param
    int param;
};

/**
 * @brief The ControllerListener interface
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
 * @brief The Controller class
 */
class Controller {
  public:
    /**
     * @brief Controller
     * @param i
     */
    Controller(GameLib::Input *i);

    /**
     * @brief ~Controller
     */
    virtual ~Controller();

    /**
     * @brief Update
     */
    virtual void Update();

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

    /// some convenient flags to get the current status
    bool LEFT = false, RIGHT = false, UP = false, DOWN = false;

  protected:
    /// the hardware this controller is based on (eg keyboard, xbox gamepad,
    /// joystick etc)
    GameLib::Input *input;

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
