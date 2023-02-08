#include <iostream>
#include <map>
#include "TradeDef.h"

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

private:
    std::map<double, double> BUY_map;
    std::map<double, double> SELL_map;

};