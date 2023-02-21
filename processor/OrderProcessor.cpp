#include "OrderProcessor.h"
#include "TradeDef.h"
#include "ResponseSender.h"
#include "OrderBookDef.h"
#include "OrderBookHandler.h"
#include <map>
#include <math.h>
#include <iomanip>
#include <unistd.h>

using namespace std;

OrderProcessor::OrderProcessor()
{
    responseSender = new ResponseSender;
    //orderBookHandler = new OrderBookHandler;

}

OrderProcessor::~OrderProcessor()
{
    delete responseSender;
    //delete orderBookHandler;
}

bool OrderProcessor::process(OrderRequest orderRequest)
{

    std::cout << "OrderProcessor->process Start" << endl;
    bool isProcessWorked = false;

    startProcess(orderRequest);

    Response response;

    response.state = "success";
    response.comment = "success";
    response.orderId = "1";

    responseSender->sendResponse(response);

    isProcessWorked = true;
    return isProcessWorked;
}
bool getBUY_map(std::map<double, double> &buy_map)
{
    OrderBookHandler orderBookHandler;
}
bool getSELL_map(std::map<double, double> &sell_map)
{

}

int CompareDoubleAbsoulte(double x, double y, double absTolerance = (1.0e-8))
{
    double diff = x - y;
    if (fabs(diff) <= absTolerance)
        return 0;

    return (diff > 0) ? 1 : -1;
}

bool OrderProcessor::startProcess(OrderRequest orderRequest)
{
    //sleep(20);
    cout << "Start Process" << endl;

    bool isSeperateOrderWorked = false;

    User user; // 임시
    user.assets = 100000000.0;
    user.balance = 100000000.0;

    OrderBookHandler orderBookHandler;
    

    checkOrder(orderRequest, user);
    std::cout<< "startProcess orderRequest : " << orderRequest.symbol << " side : " << TradeDataUtil::getSideStr(orderRequest.side) << " price : " << orderRequest.price << " qty : " << orderRequest.qty<<endl; 

    orderBookHandler.registerOrderBook(orderRequest.price, orderRequest.qty, orderRequest.side, orderRequest.symbol);
    orderBookHandler.concludeContract();
    orderBookHandler.printMap();

    // 1. 주문이 유효한지 확인
    // 2. 주문이 어떤건지 확인 하고
    // 3. 주문 확인 해서 체결되는거면 오더북 등록 하지 말고 바로 체결
    // 4. 오더북 등록
    // 5. 오더북 상 체결가능한 상품이면 체결

    /*if (orderRequest.side == EN_BUY)
    {
        //if (!orderBookHandler.comparePriceMap(orderRequest.price, orderRequest.qty, EN_BUY) )
        //{
        //    
        //}

    

        //for (auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        //{
        //    if (0 >= CompareDoubleAbsoulte(orderRequest.price, itr->first))
        //    {
        //
        //        if (orderRequest.qty <= itr->second)
        //            return true;  //OrderBookErrorMessage::EN_GET_ENOUTH_QTY;
        //        else
        //        {
        //            //std::cout << "try register orderbook price : " << orderRequest.price << "qty : " << orderRequest.qty << endl;
        //            //registerOrderBook(price, qty, EN_BUY);
        //        }
        //    }
        //    else
        //        return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE;
        //}
    }
    else if (EN_side == EN_SELL)
    {
        for (auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
        {
            if (0 == CompareDoubleAbsoulte(price, itr->first))
            {
                if (qty <= itr->second)
                    return OrderBookErrorMessage::EN_GET_ENOUTH_QTY;
                else if (itr->second == 0)
                    return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE;
                // 구매 가능한 수량이 0이라고 해서 map의 키에 존재 하지 않을거란 보장이 없음

                else
                {
                    std::cout << "try register orderbook price : " << price << "qty : " << qty << endl;
                    registerOrderBook(price, qty, EN_BUY);
                }

                // 주문 수량보다 작을 경우 적은 숫자 만큼만 체결 될 수 있도록 처리
                // 함수를 따로 빼야할듯
            }
            else
                return OrderBookErrorMessage::EN_NOT_MATCHED_PRICE;
        }
    }*/

    //double orderbookQty;
    //if (orderBookHandler.getQtyByPrice(orderRequest.price, orderbookQty, EN_BUY) == OrderBookErrorMessage::EN_GET_ENOUTH_QTY)
    //{
    //    // 처리
    //    orderBookHandler.setOrderbook(orderRequest.price, orderbookQty - orderRequest.qty, EN_BUY);
    //}
}
ProcessorErrorMessage OrderProcessor::checkOrder(OrderRequest orderRequest, User user)
{
    if (orderRequest.orderType == EN_LIMIT)
    {
        if (orderRequest.price < 0)
            /* 가격정보를 가져와서 시세대비 플마 몇퍼센트 이런거 설정해두면 좋을듯|| orderRequest.price*/
            return ProcessorErrorMessage::EN_WRONG_PRICE;
        if (orderRequest.qty < 0)
            return ProcessorErrorMessage::EN_WRONG_QTY;
    }
    if (orderRequest.side == EN_BUY && orderRequest.price * orderRequest.qty > user.balance)
        return ProcessorErrorMessage::EN_NOT_ENOUGH_BALANCE;
    return ProcessorErrorMessage::EN_CHECK_ORDER_SUCCESS;
}