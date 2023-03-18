#pragma once
#include <iostream>
#include "OrderProcessor.h"
#include "TradeDef.h"

using namespace std;

struct orderRequest
{
    string _symbol;
    double _price;
    double _qty;
    Side _side;
    OrderType _orderType;
    string _requestId;
    string _userId;
    time_t _time;

};

class OrderProcessor;
class RequestReceiver
{
public:
    RequestReceiver();
    ~RequestReceiver();
    OrderRequest CallOrderProcessor(OrderRequest _orderRequest);

    void receiveReq(OrderRequest req);

private:
    
    OrderProcessor *orderProcessor; 
};
// 