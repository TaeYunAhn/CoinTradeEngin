#include "StateHandler.h"
#include "InitState.h"

StateHandler::StateHandler(/* args */)
{
    curState = new InitState;
    curState->setHandler(this);

    nextState = nullptr;
}

StateHandler::~StateHandler()
{
    if (curState)
        delete curState;

    if (nextState)
        delete nextState;
}

void StateHandler::setNextState(State *nextState)
{
	if( this->nextState ) {
		delete this->nextState;
		this->nextState = nullptr;
	}

	this->nextState = nextState;
}


void StateHandler::changeState()
{
	 if (nextState)
    {
        nextState->setHandler(this);

        curState = nextState;
        nextState = nullptr;
    }
}

void StateHandler::proceed()
{
	EResultCode eReturn = EResultCode::enFailed;

	while( eReturn != EResultCode::enFinished ) {
		eReturn = curState->proceed();
	}
}