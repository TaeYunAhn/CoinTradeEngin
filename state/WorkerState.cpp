#include <thread>
#include <unistd.h>
#include <vector>
#include <fstream>
#include "../lib/json/json.h"
//#include <curl/curl.h>
#include "FinalState.h"
#include "../processor/RequestReceiver.h"
#include "../processor/TradeDef.h"
#include "WorkerState.h"

using namespace std;

WorkerState::WorkerState()
{
}

WorkerState::~WorkerState()
{
}

EResultCode WorkerState::proceed()
{
    const string& path = "/home/tahn/code_trade_engine/input.json";
    std::ifstream json_dir(path.c_str());
    Json::CharReaderBuilder builder;
    builder["collectComments"] = false;
    Json::Value root;

    JSONCPP_STRING err;
    if (!parseFromStream(builder, json_dir, &root, &err))
    {
        cout << "Failed to parse json(" << path << ")" << endl;
        return EResultCode::enFailed;
    }

    if(!root.isArray())
    {
        // Exception
    }

    vector<OrderRequest> requests;
    for (const auto& elem : root)
    {
        const auto& id = elem["id"].asInt();
        const auto& orderType = elem["order_type"].asInt();
        const auto& symbol = elem["symbol"].asString();
        const auto& side = elem["side"].asString();
        const auto& price = elem["price"].asDouble();
        const auto& qty = elem["qty"].asDouble();

        requests.push_back(OrderRequest((OrderType)orderType, symbol, EN_BUY, price, qty));

    }

    RequestReceiver requestReceiver;
    for ( const auto& req : requests)
    {
        std::cout << "WorkerState proceed start"<<endl;
        requestReceiver.receiveReq(req);
    }

    ////






    

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