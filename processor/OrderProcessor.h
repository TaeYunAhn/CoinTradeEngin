#pragma once
#include "TradeDef.h"
#include "ResponseSender.h"
#include "OrderBookHandler.h"
#include <map>


class OrderProcessor
{
public:
    OrderProcessor();
    ~OrderProcessor();
    bool process(OrderRequest orderRequest);
    bool startProcess(OrderRequest orderRequest);
    ProcessorErrorMessage checkOrder(OrderRequest orderRequest, User user);
    bool ExecuteConclusion(OrderRequest orderRequest, User user, Side EN_Side);

private:
    ResponseSender* responseSender;
    OrderBookHandler orderBookHandler;

};
