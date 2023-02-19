#pragma once
#include "TradeDef.h"
#include "ResponseSender.h"
#include <map>


class OrderProcessor
{
public:
    OrderProcessor();
    ~OrderProcessor();
    bool process(OrderRequest orderRequest);
    bool startProcess(OrderRequest orderRequest);
    ProcessorErrorMessage checkOrder(OrderRequest orderRequest, User user);
    bool *getBUY_map(std::map<double, double> &buy_map);
    bool *getSELL_map(std::map<double, double> &sell_map);

private:
    ResponseSender* responseSender;
};