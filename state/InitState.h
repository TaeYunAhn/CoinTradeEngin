#pragma once
#include "StateHandler.h"
#include "WorkerState.h"

class InitState : public State
{
public:
    InitState(/* args */) {}
    virtual ~InitState() {}

    virtual EResultCode proceed() override final
    {
        
	    interface->setNextState(new WorkerState()); 
	    interface->changeState();

	    return EResultCode::enSuccess;
    }

    virtual void shutdown() override final
    {
    }

};
