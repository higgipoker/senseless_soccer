#pragma once
#include "../../player.h"
#include <gamelib/statemachine/state.h>

namespace SenselessSoccer {

/**
*@brief The BrainState class
*/
class BrainState : public GameLib::State {
public:
    /**
     * @brief BrainState
     * @param p
     */
    BrainState(Player *p);

    /**
     * @brief OnStart
     */
    virtual void OnStart() override;

    /**
     * @brief OnStep
     * @param _dt
     */
    virtual void OnStep(const float _dt) override;

    /**
     * @brief OnEnd
     */
    virtual void OnEnd() override;

    /**
     * @brief StateOver
     * @return
     */
    virtual bool StateOver() override;

    /**
     * @brief ChangeToNextState
     */
    void ChangeToNextState() override final;

    /**
     * @brief modify the state parameters on the fly
     * @param [in] mod modifier to set (set to NONE) to cancel modifiers
     */
    virtual void Modify(modifier mod);

protected:
    /// pointer back to player for sm context
    Player *player;

    /// state paramaters modifier
    std::vector<modifier> modifiers;

    /// next state to change to
    brainstate next_state;

public:
    friend class Brain;
};
}
