#include "OrderProcessor.h"    
#include "TradeDef.h"
#include "ResponseSender.h"
#include "OrderBookDef.h"
#include "OrderBookHandler.h"
#include <map>
#include <math.h>

using namespace std;

OrderProcessor::OrderProcessor() 
{
    responseSender = new ResponseSender;
}


OrderProcessor::~OrderProcessor() 
{
    delete responseSender;
}

bool OrderProcessor::process(OrderRequest orderRequest)
{

    std::cout << "OrderProcessor->process Start"<<endl;
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
    cout << "시작"<< endl;

    bool isSeperateOrderWorked = false;

    OrderBookHandler orderBookHandler; 

    // checkOrder(orderRequest, orderRequest.userId, orderRequest.side)
    // 두번째 매개변수 user 를 어떻게 가져와야 할지 생각할 것. 
    // 아마 user 데이터 핸들러를 만들어서 거기 돌려야 할듯?

    /*
    //1번
    std::map<double, double> buy_map = *orderBookHandler.getBUY_map1();
    std::map<double, double>* buy_map = orderBookHandler.getBUY_map1();
    

    // std::map<double, double> BUY_map;
    // buy_map = *&BUY_map;
    // buy_map[1.5] = 1.5;


    //2번
    std::map<double, double> *buy_map2;
    orderBookHandler.getBUY_map2(buy_map2); // call by pointer 

    // std::map<double, double> BUY_map;
    // buy_map2 = &BUY_map; 
    // buy_map2[1.5] = 2.5;


    //3번
    std::map<double, double> buy_map3;
    orderBookHandler.getBUY_map3(buy_map3); // call by reference 
    */

    // buy_map3[1.5] = 3.5;

    double orderbookQty;
    if ( orderBookHandler.getQtyByPrice(orderRequest.price, orderbookQty, EN_BUY) == EN_GET_ENOUTH_QYY)
    {
        // 처리 
        orderBookHandler.setOrderbook(orderRequest.price, orderbookQty - orderRequest.qty, EN_BUY);

    }


    // buy_map[1.5] = 1.5;
    // *(buy_map2[1.5]) = 2.5;
    // buy_map3[1.5] = 3.5;

        // 가져올 때 포인터로 가져올 것

        // 오더북에 아무것도 없으면 그냥 올릴 것.

    if(orderRequest.side == EN_BUY)
    {
        cout << "side : EN_BUY"<< endl;

        // 데이터 처리 
        // 오더북에 대한 데이터를 어떤 방식으로 저장할 것인가?
        // 데이터는 어디에 있어야 할 것인가?
        // 오더북 : 셀, 바이 각 각 map <가격, 갯수>


        for(auto itr = sell_map.begin(); itr != SELL_map.end(); itr++)
        {
            if (0 == CompareDoubleAbsoulte(orderRequest.price, itr->first))
            {
                

                if(checkQty(orderRequest, itr) == true) // enum 으로 변경 예정
                    isSeperateOrderWorked == true;
                return isSeperateOrderWorked;
            }



        }
        cout << "일치하는 주문이 없습니다."<< endl;

        return isSeperateOrderWorked;
        //EN_BUY 면 기존 orderBook 의 EN_SELL 데이터와 가격, 갯수 비교 후 체결
    }
    else if(orderRequest.side == EN_SELL)
    {

    }
}

ProcessorErrorMessage OrderProcessor::checkOrder(OrderRequest orderRequest, User user, Side side)
{
    if(orderRequest.orderType == EN_LIMIT)
    {
        if(orderRequest.price < 0) 
        /* 가격정보를 가져와서 시세대비 플마 몇퍼센트 이런거 설정해두면 좋을듯|| orderRequest.price*/
            return EN_WRONG_PRICE;
        if(orderRequest.qty < 0 )
            return EN_WRONG_QTY;
    }
    
    if(orderRequest.price * orderRequest.qty > user.balance)
        return EN_NOT_ENOUGH_BALANCE;
    
    return EN_CHECK_ORDER_SUCCESS;
}