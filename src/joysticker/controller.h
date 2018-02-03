#pragma once
#include <gamelib/input/keyboard.h>
#include <set>
namespace SenselessSoccer {

/** @brief event ids */
enum ControllerEventID { NO_EVENT = 0, FIRE_PRESS, FIRE_RELEASE, FIRE_TAP, FIRE_float_TAP };

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
    ControllerEvent (ControllerEventID i, int p = 0) {
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
    * @brief constructor
    * @param event event to handle
    */
    virtual void OnControllerEvent (ControllerEvent event) = 0;
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
    void AddListener (ControllerListener *listener);

    /**
     * @brief RemoveListener
     * @param listener listener to remove
     */
    void RemoveListener (ControllerListener *listener);

protected:
    /**
     * @brief Notify
     * @param event event to handle
     */
    void Notify (ControllerEvent event);

    /// list of listeners
    std::set<ControllerListener *> listeners;

    /// release flag
    bool wait_for_release = false;
};

} // namespace SenselessSoccer
