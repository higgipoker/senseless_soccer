#pragma once
#include <gamelib/input/keyboard.h>
#include <set>
namespace SenselessSoccer {

/** @brief event ids */
enum ControllerEventID { NO_EVENT = 0, FIRE_PRESS, FIRE_RELEASE, FIRE_TAP, FIRE_DOUBLE_TAP };

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
       * @brief constructor
       * @param event
       */
    virtual void OnControllerEvent(ControllerEvent event) = 0;
};

/**
 * @brief The SensiController class
 */
class SensiController : public GameLib::Keyboard {
  public:
    /**
     * @brief Update
     */
    void Update() override;

    /**
     * @brief AddListener
     * @param listener
     */
    void AddListener(ControllerListener *listener);

    /**
     * @brief RemoveListener
     * @param listener
     */
    void RemoveListener(ControllerListener *listener);

  protected:
    /**
     * @brief Notify
     * @param event
     */
    void Notify(ControllerEvent event);

    /// list of listeners
    std::set<ControllerListener *> listeners;
    bool wait_for_release = false;
};

} // namespace SenselessSoccer
