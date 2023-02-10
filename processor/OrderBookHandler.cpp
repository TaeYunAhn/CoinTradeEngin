#include <math.h>
#include <iostream>
#include "OrderBookHandler.h"


OrderBookHandler::OrderBookHandler()
{

}

OrderBookHandler::~OrderBookHandler()
{


}


int OrderBookHandler::CompareDoubleAbsoulte(double x, double y, double absTolerance /*= (1.0e-8)*/)
{
    double diff = x - y;
    if (fabs(diff) <= absTolerance)
        return 0;

    return (diff > 0) ? 1 : -1;
}


/*
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
*/

OrderBookErrorMessage OrderBookHandler::getQtyByPrice(const double price, double& qty, Side EN_side)
{
    // 함수 이름이 GET 인데 리턴을 QTY를 해야 하나..

    if(EN_side == EN_BUY)
    {
        for(auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        {
            if(0 >= CompareDoubleAbsoulte(price, itr->first))
            {
                if(qty <= itr->second)
                    return OrderBookErrorMessage::EN_GET_ENOUTH_QTY;
                else if(itr->second == 0)
                    return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE; 
                    //구매 가능한 수량이 0이라고 해서 map의 키에 존재 하지 않을거란 보장이 없음
                
                else
                {
                    std::cout<< "try register orderbook price : " << price << "qty : " << qty<<endl;     
                    registerOrderBook(price, qty, EN_BUY);
                }
                // 주문 수량보다 작을 경우 적은 숫자 만큼만 체결 및 나머지 오더북 등록 될 수 있도록 처리 
                // 함수를 따로 빼야할듯
            }
            else
                return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE;
        }
    }

    else if(EN_side == EN_SELL)
    {
        for(auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        {
            if(0 == CompareDoubleAbsoulte(price, itr->first))
            {
                if(qty <= itr->second)
                    return OrderBookErrorMessage::EN_GET_ENOUTH_QTY;
                else if(itr->second == 0)
                    return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE; 
                    //구매 가능한 수량이 0이라고 해서 map의 키에 존재 하지 않을거란 보장이 없음
                
                else
                {
                    std::cout<< "try register orderbook price : " << price << "qty : " << qty<<endl;     
                    registerOrderBook(price, qty, EN_BUY);

                }

                // 주문 수량보다 작을 경우 적은 숫자 만큼만 체결 될 수 있도록 처리 
                // 함수를 따로 빼야할듯
            }
            else
                return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE;
        }
    }
}
OrderBookErrorMessage OrderBookHandler::setOrderbook(const double price, double qty, Side EN_side)
{
    if(EN_side == EN_BUY)
    {
        for(auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        {
            itr->second = qty;
            // 양방 유저 데이터(잔액, 포지션, 코인 수 등) 업데이트 처리 필요
            return OrderBookErrorMessage::EN_CONCLUSION_SUCCESS;
        }
    }

    else if(EN_side == EN_SELL)
    {
      for(auto itr = BUY_map.begin(); itr != BUY_map.end(); itr++)
        {
            itr->second = qty;
            // 양방 유저 데이터(잔액, 포지션, 코인 수 등) 업데이트 처리 필요
            return OrderBookErrorMessage::EN_CONCLUSION_SUCCESS;
        }
    }
}
 
bool OrderBookHandler::registerOrderBook(double price, double qty, Side EN_side)
{
    if(EN_side == EN_BUY)
    {
        for(auto itr = BUY_map.begin(); itr != BUY_map.end(); itr++)
        {
            if(0 == CompareDoubleAbsoulte(price, itr->first))
            {
                BUY_map[price] += qty;
                std::cout<< "orderbook registered price : " << price << "qty : " << qty<<endl; 
            }

        }
        BUY_map[price] = qty;
        std::cout<< "orderbook registered price : " << price << "qty : " << qty<<endl; 

    }
    else if (EN_side == EN_SELL)
    {
        for(auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        {
            if(0 == CompareDoubleAbsoulte(price, itr->first))
            {
                SELL_map[price] += qty;
                std::cout<< "orderbook registered price : " << price << "qty : " << qty<<endl; 

            }
                

        }
        SELL_map[price] = qty;
                std::cout<< "orderbook registered price : " << price << "qty : " << qty<<endl; 

    }
}
