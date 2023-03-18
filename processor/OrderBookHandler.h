#pragma once
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>
#include "TradeDef.h"

using namespace std;

struct QtyData 
{
    double totalQTY;
    vector<pair<string, double>> userSequence; // userId, qty
};


class OrderBookHandler
{
public:
    OrderBookHandler();
    ~OrderBookHandler();

    std::map<double, QtyData> *getBUY_map(std::map<double, QtyData> *buy_map);
    std::map<double, QtyData> *getSELL_map(std::map<double, QtyData> *sell_map);
    
    std::map<double, QtyData>* getBUY_map1();
    std::map<double, QtyData>* getSELL_map1();

    void getBUY_map2(std::map<double, QtyData> *buy_map);
    void getBUY_map3(std::map<double, QtyData> &buy_map);
    void getSELL_map2(std::map<double, QtyData> *sell_map);
    
    OrderBookErrorMessage getQtyByPrice(const double price, double& qty, Side EN_side);
    OrderBookErrorMessage setOrderbook(const double price, double qty, Side EN_side);
    bool registerOrderBook(double price, double qty, Side EN_side, std::string symbol);
    int CompareDoubleAbsoulte(double x, double y, double absTolerance = (1.0e-8));
    double setAppropriatePrice(std::map<double, QtyData> check_map, Side EN_side); // 최저가, 최고가 셋
    bool printMap();
    bool comparePriceMap(double price, double qty, Side EN_side);
    bool concludeContract(double price, double qty, Side EN_side);
    double checkExistContract(double price, double qty, Side EN_side);
    bool deleteContract(double price, double qty, Side EN_ssdide);
private:
    std::map<double, QtyData> BUY_map;
    std::map<double, QtyData> SELL_map;
    //double curPrice;
    std::map<map<double, QtyData>, map<double, QtyData>> OrderBook_map;

};