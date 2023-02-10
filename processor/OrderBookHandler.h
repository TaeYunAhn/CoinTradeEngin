#pragma once
#include <iostream>
#include <map>
#include <queue>
#include "TradeDef.h"

using namespace std;

class OrderBookHandler
{
public:
    OrderBookHandler();
    ~OrderBookHandler();

    std::map<double, double> *getBUY_map(std::map<double, double> *buy_map);
    std::map<double, double> *getSELL_map(std::map<double, double> *sell_map);
    
    std::map<double, double>* getBUY_map1();
    void getBUY_map2(std::map<double, double> *buy_map);
    void getBUY_map3(std::map<double, double> &buy_map);
    
    OrderBookErrorMessage getQtyByPrice(const double price, double& qty, Side EN_side);
    OrderBookErrorMessage setOrderbook(const double price, double qty, Side EN_side);
    bool registerOrderBook(double price, double qty, Side EN_side);
    int CompareDoubleAbsoulte(double x, double y, double absTolerance = (1.0e-8));


private:
    std::map<double, double> BUY_map;
    std::map<double, double> SELL_map;
    double curPrice;
    std::map<map<double, double>, map<double, double>> OrderBook_map;

};