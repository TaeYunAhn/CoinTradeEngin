#include "OrderBookHandler.h"

OrderBookHandler::OrderBookHandler()
{

}

OrderBookHandler::~OrderBookHandler()
{


}
//1번 방법 : 매개변수 없이 하는 법
std::map<double, double>* OrderBookHandler::getBUY_map1()
{
    return &BUY_map;
}
//2번 : 매개변수로 담아오는 것
void OrderBookHandler::getBUY_map2(std::map<double, double> *buy_map)
{
    buy_map = &BUY_map; 
    
}
//3번 : 레퍼런스로 가져오는 법
void OrderBookHandler::getBUY_map3(std::map<double, double> &buy_map)
{
    buy_map = BUY_map;
}

std::map<double, double>* OrderBookHandler::getSELL_map()
{
    return &SELL_map;
}

