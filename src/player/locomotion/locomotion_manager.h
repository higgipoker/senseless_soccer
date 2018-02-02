#pragma once

#include <queue>
#include <gamelib/statemachine/state_machine.h>

#include "arrive.h"
#include "head.h"
#include "pursue.h"
#include "intercept.h"

namespace SenselessSoccer {

class Player;
class LocomotionManager : public GameLib::StateMachine {
public:
    /**
     * @brief constructor
     * @param [in] p pointer back to player for state machine context
     */
    explicit LocomotionManager(Player *p);

    /**
     * @brief update
     * @param [in] dt time delta
     */
    void UpdateLocomotion(double dt);

    /**
     * @brief activate the arrive locomotion
     */
    void ActivateArrive(GameLib::Vector3 dest);

    /**
     * @brief activate the pursue locomotion
     */
    void ActivatePursue(GameLib::Physical *follow);

    /**
     * @brief activate the head locomotion
     */
    void ActivateHead(GameLib::Vector3 dir);

    /**
     * @brief activate the intercept locomotion
     */
    void ActivateIntercept(GameLib::Physical *follow);

    /**
     * @brief cancel all locomotion
     */
    void Cancel(void);

private:
    /// ref back to player
    Player &player;

    /// current locomition behaviour
    Locomotion *behaviour;

    /// an arrive behaviour
    Arrive arrive;

    /// a pursue locomotion
    Pursue pursue;

    ///  a head ocomotion
    Head head;

    // an intercept behaviour
    Intercept intercept;

    /// locomotion queue
    std::queue<Locomotion *> behaviour_queue;

    /// helper to change locomotion
    void change_locomotion(Locomotion &b);
};

} // namespace SenselessSoccer
