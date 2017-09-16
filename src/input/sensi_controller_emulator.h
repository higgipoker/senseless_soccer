#pragma once
#include "sensi_controller.h"
#include <vector>
namespace SenselessSoccer {

/** @brief a programmed event */
struct ProgrammedEvent {

    /// input type
    int evt;

    /// frames the input lasts for
    int frames;
};

/**
 * @brief The ControllerEmulator class
 */
class ControllerEmulator {
  public:
    /**
    * @brief constructor
    */
    ControllerEmulator(void);

  protected:
    /// a list of events
    std::vector<ProgrammedEvent> programmed_events;
};

} // namespace SenselessSocccer
