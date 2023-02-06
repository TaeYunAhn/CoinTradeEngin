#pragma once

class State;
class StateInterface
{
public:
    virtual void setNextState(State *nextState) = 0;
    virtual void changeState() = 0;
    virtual ~StateInterface(){}
};