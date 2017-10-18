#include "controller.h"

namespace SenselessSoccer {

// ------------------------------------------------------------
// Update
// ------------------------------------------------------------
void Controller::Update() {
	// to track if fire down has changed, save state before base update
	int prev_fire_state = event_states[GameLib::FIRE_DOWN];

	GameLib::Keyboard::Update();

	if (prev_fire_state) {
		if (event_states[GameLib::FIRE_UP]) {
			Notify(ControllerEvent(FIRE_RELEASE, event_states[GameLib::FIRE_LENGTH_CACHED]));
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
