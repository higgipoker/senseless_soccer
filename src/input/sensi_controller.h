#pragma once
#include <set>
#include <gamelib/input/keyboard.h>
namespace SenselessSoccer {

enum ControllerEventID {
    NO_EVENT = 0,
    FIRE_PRESS,
    FIRE_RELEASE,
    FIRE_TAP,
    FIRE_DOUBLE_TAP
};

struct ControllerEvent {
    ControllerEvent() {
        id = NO_EVENT;
        param = 0;
    }
    ControllerEvent(ControllerEventID i, int p = 0) {
        id = i;
        param = p;

    }
    ControllerEventID id;
    int param;
};

class ControllerListener {
public:
    virtual void OnControllerEvent(ControllerEvent event) = 0;
};

class SensiController : public GameLib::Keyboard {
public:
    void Update() override;
    void AddListener(ControllerListener *listener);
    void RemoveListener(ControllerListener *listener);

protected:
    void Notify(ControllerEvent event);
    std::set<ControllerListener *> listeners;
    bool wait_for_release = false;
};
}
