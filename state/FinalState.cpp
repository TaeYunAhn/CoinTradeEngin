
#include "FinalState.h"

FinalState::FinalState(/* args */)
{
}

FinalState::~FinalState()
{
}

EResultCode FinalState::proceed()
{
    shutdown();
	return EResultCode::enFinished;
}

void FinalState::shutdown()
{
    }
