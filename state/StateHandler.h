#pragma once
#include "State.h"
#include "StateInterface.h"

class StateHandler : public StateInterface
{
public:
    StateHandler(/* args */);
    virtual ~StateHandler();

    virtual void changeState() override final;
	virtual void setNextState(State *nextState) override final;
    void proceed();

private:
    State* curState;
    State* nextState;
};
