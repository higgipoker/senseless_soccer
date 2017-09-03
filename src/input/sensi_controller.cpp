#include "sensi_controller.h"

namespace SenselessSoccer {

void SensiController::Update() {
    // to track if fire down has changed
    int prev_fire_state = event_states[GameLib::FIRE_DOWN];

    GameLib::Keyboard::Update();


    if(prev_fire_state) {
        if(event_states[GameLib::FIRE_UP]) {
            Notify(ControllerEvent(FIRE_RELEASE, event_states[GameLib::FIRE_LENGTH_CACHED]));
        }

    } else {
        if(event_states[GameLib::FIRE_DOWN]) {
            Notify(ControllerEvent(FIRE_PRESS));
        }
    }
}

void SensiController::AddListener(SenselessSoccer::ControllerListener *listener) {
    listeners.insert(listener);
}

void SensiController::RemoveListener(SenselessSoccer::ControllerListener *listener) {
    listeners.erase(listeners.find(listener));
}


void SensiController::Notify(SenselessSoccer::ControllerEvent event) {
    for(auto it = listeners.begin(); it != listeners.end(); ++it) {
        (*it)->OnControllerEvent(event);
    }
}

}// namespace SenselessSoccer
