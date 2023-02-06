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


    // buy_map3[1.5] = 3.5;

    double orderbookQty;
    if ( !orderBookHandler.getQtyByPrice(orderRequest.price, orderbookQty, true) )
    {
        // 처리 
    }

    orderBookHandler.setOrderbook(orderRequest.price, orderbookQty - orderRequest.qty);


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
                cout << "구매가격 판매가격 일치 확인 성공"<< endl;

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

bool OrderProcessor::checkQty(OrderRequest orderRequest,  map<double, double>::iterator itr)
{
    bool IsCheckQtyWorked = false;
    //for(auto itr = SELL_map.begin(); itr != SELL_map.end(); itr++)
    {
        if(orderRequest.qty <= itr->second)
        {
            // 체결 성공 후 itr->second 에서 체결된 갯수만큼 빼줌
            // 유저 데이터 핸들러를 가져와서 체결된 양 측의 보유 주식 수 + 계좌 잔액등을 수정해줘야 함
            itr->second -= orderRequest.qty;
            cout << "구매 성공"<< endl;
        }
        
    }
    IsCheckQtyWorked = true;
    return IsCheckQtyWorked; // 나중에 enum 으로 변경예정
}