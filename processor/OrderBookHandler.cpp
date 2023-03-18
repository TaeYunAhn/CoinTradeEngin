#include <math.h>
#include <iostream>
#include <string>
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



//1번 방법 : 매개변수 없이 하는 법
std::map<double, QtyData>* OrderBookHandler::getBUY_map1()
{
    return &BUY_map;
}
std::map<double, QtyData>* OrderBookHandler::getSELL_map1()
{
    return &SELL_map;
}

//2번 : 매개변수로 담아오는 것
void OrderBookHandler::getBUY_map2(std::map<double, QtyData> *buy_map)
{
    buy_map = &BUY_map; 
    
}
//3번 : 레퍼런스로 가져오는 법
void OrderBookHandler::getBUY_map3(std::map<double, QtyData> &buy_map)
{
    buy_map = BUY_map;
}

//std::map<double, QtyData>* OrderBookHandler::getSELL_map()
//{
//    return &SELL_map;
//}

void OrderBookHandler::getSELL_map2(std::map<double, QtyData> *sell_map)
{
    sell_map = &SELL_map; 
    
}

double OrderBookHandler::checkExistContract(double price, double qty, Side EN_side)
{
    double tempPrice = 0;
    
    if(EN_side == EN_BUY)
    {
        if (SELL_map.begin()->first <= price)
            tempPrice = SELL_map.begin()->first;
        
    }
    else if(EN_side == EN_SELL)
    {
        if (BUY_map.rbegin()->first >= price)
             tempPrice = BUY_map.rbegin()->first;
    }

    return tempPrice;
    
    
}


bool OrderBookHandler::deleteContract(double price, double qty, Side EN_side)
{
    bool deleteContract = false;
    if(EN_side == EN_BUY)
    {
        SELL_map[price].totalQTY -= qty;
        deleteContract = true;
    }
    else if(EN_side == EN_SELL)
    {
        BUY_map[price].totalQTY -= qty;
        deleteContract = true;
    }
    return deleteContract;

}

bool OrderBookHandler::concludeContract(double price, double qty, Side EN_side)
{
    bool isContractWorked = false;
    return isContractWorked;
}


bool OrderBookHandler::printMap()
{
    for(auto itr = BUY_map.begin(); itr != BUY_map.end(); itr++)
        cout << "BUY_map price : "<<itr->first << " qty : " << itr->second.totalQTY <<endl;
    for(auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        cout << "SELL_map price : "<<itr->first << " qty : " << itr->second.totalQTY <<endl;
}

bool OrderBookHandler::comparePriceMap(double price, double qty, Side EN_side)
{

    //if(SELL_map.find(price) == SELL_map.end())
    //    return false;
    //else
    //    return true;
    /*for(auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        {
            if(0 >= CompareDoubleAbsoulte(price, itr->first))
            {
                
                if(qty <= itr->second)
                    return OrderBookErrorMessage::EN_GET_ENOUTH_QTY;
                else
                {

                    std::cout<< "try register orderbook price : " << price << "qty : " << qty<<endl;     
                    registerOrderBook(price, qty, EN_BUY);
                }
            }
            else
                return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE;*/
}


OrderBookErrorMessage OrderBookHandler::getQtyByPrice(double price, double& qty, Side EN_side)
{
    cout << "Start getQtyByPrice"<<endl;
    // 함수 이름이 GET 인데 리턴을 QTY를 해야 하나..
    int temp_price = 0;
    if(EN_side == EN_BUY)
    {
        //if(price >= SELL_map.begin()->first) //구매 희망가격이 판매 희망가격 보다 높거나 같을 경우
        //{
        //    temp_price = SELL_map.begin()->first; // 
        //}
        //if(BUY_map.find(price) == BUY_map.end())
        //{
        //    BUY_map[price] = qty;
        //}
        //else if(BUY_map.find(price) != BUY_map.end())
        //{
        //    BUY_map[price] += qty;
        //}
    }


    /*else if(EN_side == EN_SELL)
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
                    //egisterOrderBook(price, qty, EN_BUY);

                }

                // 주문 수량보다 작을 경우 적은 숫자 만큼만 체결 될 수 있도록 처리 
                // 함수를 따로 빼야할듯
            }
            else
                return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE;
        }
    }*/

}

double OrderBookHandler::setAppropriatePrice(std::map<double, QtyData> check_map, Side EN_side)
{
    //if(EN_side == EN_BUY) // set map serch
    //{
    //    
    //}
    //else if(EN_side == EN_SELL) // buy map serch
    //{
    //
    //}
}



OrderBookErrorMessage OrderBookHandler::setOrderbook(const double price, double qty, Side EN_side)
{
    if(EN_side == EN_BUY)
    {
        for(auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        {
            itr->second.totalQTY = qty;
            // 양방 유저 데이터(잔액, 포지션, 코인 수 등) 업데이트 처리 필요
            return OrderBookErrorMessage::EN_CONCLUSION_SUCCESS;
        }
    }

    else if(EN_side == EN_SELL)
    {
      for(auto itr = BUY_map.begin(); itr != BUY_map.end(); itr++)
        {
            itr->second.totalQTY = qty;
            // 양방 유저 데이터(잔액, 포지션, 코인 수 등) 업데이트 처리 필요
            return OrderBookErrorMessage::EN_CONCLUSION_SUCCESS;
        }
    }
}
 
bool OrderBookHandler::registerOrderBook(double price, double qty, Side EN_side, std::string symbol)
{
    bool isregisterWorked = false;
    //concludeContract();
    if(EN_side == EN_BUY)
    {   
                BUY_map[price].totalQTY += qty; 
                std::cout<< "orderbook registered symbol : " << symbol << " side : " << TradeDataUtil::getSideStr(EN_side) << " price : " << price << " qty : " << qty<<endl; 
                isregisterWorked = true;
    }
    else if (EN_side == EN_SELL)
    {
                SELL_map[price].totalQTY += qty;
                std::cout<< "orderbook registered symbol : " << symbol << " side : " << TradeDataUtil::getSideStr(EN_side) << " price : " << price << " qty : " << qty<<endl; 
                isregisterWorked = true;
    }
    return isregisterWorked;
}

// 디버깅 시작하겠습니다.