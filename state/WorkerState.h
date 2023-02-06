#pragma once
#include <condition_variable>
#include "State.h"

class CLogger;
class WorkerState : public State
{
public:
    WorkerState();
    virtual ~WorkerState();

    virtual EResultCode proceed() override final;
    virtual void shutdown() override final;

private:
    CLogger* logger;
    std::condition_variable terminateMainCond;
};
