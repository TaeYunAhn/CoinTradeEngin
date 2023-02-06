#pragma once
#include <iostream>
#include <string>
#include "TradeDef.h"

using namespace std;

class OrderProcessor;
struct Response
{
    string state;
    string comment;
    string orderId;
};

class ResponseSender
{
public:

    ResponseSender();
    ~ResponseSender();

    bool sendResponse(Response response);

private:
    OrderProcessor* orderProcessor;
};