#pragma once

#include <gamelib/statemachine/state.h>

namespace SenselessSoccer {

class TeamState : public GameLib::State {
public:
    /**
     * @brief constructor
     */
    TeamState();

    /**
     * @brief destructor
     */
    virtual ~TeamState();

    /**
     * @brief onStart
     */
    virtual void OnStart() override;

    /**
     * @brief onStep
     * @param _dt time delta
     */
    virtual void OnStep (const float _dt) override;

    /**
     * @brief onEnd
     */
    virtual void OnEnd() override;

    /**
     * @brief stateOver
     */
    virtual bool StateOver() override;

    /**
     * @brief changeToNextState
     */
    virtual void ChangeToNextState() override;

protected:
};

}// SenselessSoccer
