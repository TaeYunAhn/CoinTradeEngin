#pragma once
#include "StateInterface.h"

enum class EResultCode
{
    enFailed,
    enSuccess,
    enFinished
};

class State
{

public:
    State() : interface(nullptr) {}
    virtual ~State() {}

    virtual EResultCode proceed() { return EResultCode::enFailed; }
    virtual void shutdown() = 0;

    void setHandler(StateInterface* i) { interface = i; }

protected:
    StateInterface* interface;

};