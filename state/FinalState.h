#pragma once
#include "State.h"

class FinalState;
class FinalState : public State
{
public:
    FinalState(/* args */);
    virtual ~FinalState();

    virtual EResultCode proceed() override final;
    virtual void shutdown() override final;


};