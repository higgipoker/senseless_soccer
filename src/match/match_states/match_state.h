#pragma once

#include <gamelib/statemachine/state.h>

namespace SenselessSoccer {

class MatchState : public GameLib::State {
public:
    /**
      * @brief constructor
      */
    MatchState();

    /**
     * @brief destructor
     */
    virtual ~MatchState();

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
