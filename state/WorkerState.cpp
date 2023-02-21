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
    orderRequest.symbol = "BTC";
    orderRequest.side = EN_BUY;
    orderRequest.price = 2000.00; // 키 1
    orderRequest.qty = 2000; // 밸류 1
    
    
    std::cout << "orderRequest2 register start"<<endl;

    OrderRequest orderRequest2;
    orderRequest2.orderType = EN_MARKET;
    orderRequest2.symbol = "BTC";
    orderRequest2.side = EN_BUY;
    orderRequest2.price = 3000.01; // 키 2
    orderRequest2.qty = 3000; // 밸류 2




    RequestReceiver requestReceiver;
    requestReceiver.receiveReq(orderRequest);
    requestReceiver.receiveReq(orderRequest2);

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

    interface->setNextState(new FinalState());
	interface->changeState();

	return EResultCode::enSuccess;
}

void WorkerState::shutdown()
{
}