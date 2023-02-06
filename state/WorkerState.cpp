#include <thread>
#include <unistd.h>
#include <vector>
//#include <curl/curl.h>
#include "FinalState.h"
#include "WorkerState.h"
#include "../processor/RequestReceiver.h"
#include "../processor/TradeDef.h"

using namespace std;

WorkerState::WorkerState()
{
}

WorkerState::~WorkerState()
{
}

EResultCode WorkerState::proceed()
{
    std::cout << "WorkerState proceed start"<<endl;
    OrderRequest orderRequest;
    orderRequest.orderType = EN_MARKET;
    orderRequest.price = 3000.01;
    orderRequest.qty = 31.31;




    RequestReceiver requestReceiver;
    requestReceiver.receiveReq(orderRequest);

    // //const auto& settings = CSettings::getInstance();
    
	// //curl_global_init(CURL_GLOBAL_ALL);
    // //std::vector<ThreadCtl> connectors; 
    // vector<pair<ConnectorType, thread>> connectors;
    // //vector<thread> connectors;

    // const auto& initiatorKeySet = connectorPool->getInitiatorKeySet();
    // const auto& acceptorKeySet = connectorPool->getAcceptorKeySet();

    // //LOG_INFO(logger, "%u, %u", initiatorKeySet.size(), acceptorKeySet.size());
    // for ( const auto& type : initiatorKeySet )
    // {
    //     //ThreadCtl ctl;
    //     //ctl.thread = thread{ &InitiatorBase::start, connectorPool->getInitiator(type) };
    //     //ctl.type = type;

    //     auto t = thread{ &InitiatorBase::start, connectorPool->getInitiator(type) };
    //     connectors.push_back(make_pair(type, std::move(t)));
    // }

    // for ( const auto& type : acceptorKeySet )
    // {
    //     //ThreadCtl ctl;
    //     //ctl.thread = thread{ &AcceptorBase::start, connectorPool->getAcceptor(type) };
    //     //ctl.type = type;

    //     auto t = thread{ &AcceptorBase::start, connectorPool->getAcceptor(type) };
    //     connectors.push_back(make_pair(type, std::move(t)));
    //     //connectors.push_back(std::move(ctl));
    // }


    // //terminateMainCond.wait(lock);

    // //connectorPool->shutdown();
 
    // for ( auto& conn : connectors )
    // {
    //     if ( conn.second.joinable() )
    //     {
    //         LOG_INFO(logger, "Wait to join...(%u)", static_cast<unsigned int>(conn.first));
    //         conn.second.join();
    //         LOG_WARN(logger, "Thread has been joined(%u)", static_cast<unsigned int>(conn.first));
    //     }
    // }
    
	// //curl_global_cleanup();

    // interface->setNextState(new FinalState());
	// interface->changeState();

	// return EResultCode::enSuccess;
}

void WorkerState::shutdown()
{
}