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
}

OrderProcessor::~OrderProcessor()
{
    delete responseSender;
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

bool getBUY_map(std::map<double, QtyData> &buy_map)
{
    OrderBookHandler orderBookHandler;
}

bool getSELL_map(std::map<double, QtyData> &sell_map)
{

}

int CompareDoubleAbsoulte(double x, double y, double absTolerance = (1.0e-8))
{
    double diff = x - y;
    if (fabs(diff) <= absTolerance)
        return 0;

    return (diff > 0) ? 1 : -1;
}

//  0. 기능 테스트
//  1. 유닛 테스트
//  2. 유닛 테스트를 기반으로 테스트 케이스 만들어서 넣는 방식
//  3. 부하 테스트 (한꺼번에 트레픽이 몰렸을때)
//  4. 성능 테스트 (시간이 금방 처리하냐) 


bool OrderProcessor::startProcess(OrderRequest orderRequest)
{
    sleep(20);
    cout << "Start Process" << endl;

    bool isSeperateOrderWorked = false;

    User user1; // 임시
    user1.assets = 100000000.0;
    user1.balance = 100000000.0;
    user1.wallet.qty = 100;

    User user2; // 임시
    user2.assets = 100000000.0;
    user2.balance = 100000000.0;
    user2.wallet.qty = 100;

    //OrderBookHandler orderBookHandler;
    
    checkOrder(orderRequest, user1);
    std::cout<< "startProcess orderRequest : " << orderRequest.symbol << " side : " << TradeDataUtil::getSideStr(orderRequest.side) << " price : " << orderRequest.price << " qty : " << orderRequest.qty<<endl; 
    //if (orderBookHandler.checkExistContract(orderRequest.price, orderRequest.qty, orderRequest.side) != 0)
    //    ExecuteConclusion(orderRequest, user1, orderRequest.side);
    

    // 1. 주문이 유효한지 확인
    // 2. 주문이 어떤건지 확인 하고
    // 3. 주문 확인 해서 체결되는거면 오더북 등록 하지 말고 바로 체결
    // 4. 오더북 등록
    // 5. 오더북 상 체결가능한 상품이면 체결   
    
    map<double, QtyData>buy_map;
    map<double, QtyData>sell_map;
    
    orderBookHandler.getBUY_map2(&buy_map);
    orderBookHandler.getSELL_map2(&sell_map);
    checkOrder(orderRequest, user1);
    /*while(orderRequest.qty != 0 || !buy_map.empty() || !sell_map.empty())
    {
        if(orderRequest.side == EN_BUY)
        {
            if(sell_map.begin()->first <= orderRequest.price)
            {
                //getQtyByPrice
                while(sell_map.find(orderRequest.price)->second.totalQTY != 0)
                {
                    if(sell_map.find(orderRequest.price)->second.totalQTY >= orderRequest.qty)
                    {
                        sell_map.find(orderRequest.price)->second.totalQTY -= orderRequest.qty;
                        //setExecuteContract 나중에 함수로..
                        double tempPrice = orderRequest.price * orderRequest.qty;
                        user1.assets += tempPrice;
                        user1.wallet.qty -= orderRequest.qty;
                        user2.assets -= tempPrice;
                        user2.wallet.qty += orderRequest.qty;
                    }
                    else if(sell_map.find(orderRequest.price)->second.totalQTY < orderRequest.qty)
                    {
                        double tempQty = orderRequest.qty - sell_map.find(orderRequest.price)->second.totalQTY;
                        //sell_map.find(orderRequest.price)->second.totalQTY -= tempQty;
                        orderRequest.qty -= tempQty;
                        //setExecuteContract
                        double tempPrice = orderRequest.price * tempQty;
                        user1.assets += tempPrice;
                        user1.wallet.qty += orderRequest.qty;
                        user2.assets -= tempPrice;
                        user2.wallet.qty += orderRequest.qty;

                    }     
                }
            }
            if(orderRequest.side == EN_SELL)
            {
                if(buy_map.rbegin()->first <= orderRequest.price);
                {
                    //getQtyByPrice
                    while(buy_map.find(orderRequest.price)->second.totalQTY != 0)
                    {
                        if(buy_map.find(orderRequest.price)->second.totalQTY >= orderRequest.qty)
                        {
                            buy_map.find(orderRequest.price)->second.totalQTY -= orderRequest.qty;
                            //setExecuteContract 나중에 함수로..
                            double tempPrice = orderRequest.price * orderRequest.qty;
                            user2.assets += tempPrice;
                            user2.wallet.qty += orderRequest.qty;
                            user1.assets -= tempPrice;
                            user1.wallet.qty += orderRequest.qty;
                        }
                        else if(buy_map.find(orderRequest.price)->second.totalQTY < orderRequest.qty)
                        {
                            double tempQty = buy_map.find(orderRequest.price)->second.totalQTY - orderRequest.qty;
                            buy_map.find(orderRequest.price)->second.totalQTY -= tempQty;
                            orderRequest.qty -= tempQty;
                            //setExecuteContract
                            double tempPrice = orderRequest.price * tempQty;
                            user2.assets += tempPrice;
                            user2.wallet.qty += orderRequest.qty;
                            user1.assets -= tempPrice;
                            user1.wallet.qty += orderRequest.qty;

                        }
                    } 
                }            
            }
        }
    
    }*/

    orderBookHandler.registerOrderBook(orderRequest.price, orderRequest.qty, orderRequest.side, orderRequest.symbol);
    orderRequest.qty = 0;
    //orderBookHandler.concludeContract(); 
    orderBookHandler.printMap();
}


bool OrderProcessor::ExecuteConclusion(OrderRequest orderRequest, User user, Side EN_Side)
{
    bool isExecuted = false;
    if(EN_Side == EN_BUY)
    {
        //double tempPrice = checkExistContract(orderRequest.price, orderRequest.qty, orderRequest.side);
        // //sellmap의 begin 부터 처리를 해야함
        //while (orderRequest.qty != 0 || tempPrice <= orderRequest.price)
        //{
        //    tempPrice = checkExistContract(orderRequest.price, orderRequest.qty, orderRequest.side);
        //    deleteContract();
        //}
    }
    return isExecuted;
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

/*

시도해 본 것들

1. 소수점 오차 때문인가? -> map의 키밸류 타입 변경해서 넣음 int, string 시도해봄 => 안됨. 애초에 이 문제는 아닐거라 생각함
2. 74번 줄 OrderBookHandler 를 임시객체로 써서 그런가? 
=> 맴버로 *orderBookHandler를 넣어주고, 생성자와 소멸자에 생성 삭제 해줌 => 안됨
=> 그래서 포인터로 orderBookHandler를 포인터 말고 그냥 넘겨줌 
=> CoinTradeEngine.out: malloc.c:2617: sysmalloc: Assertion `(old_top == initial_top (av) && old_size == 0) || ((unsigned long) (old_size) >= MINSIZE && prev_inuse (old_top) && ((unsigned long) old_end & (pagesize - 1)) == 0)' failed.
실행시, 이런 오류가 뜸 => 안되는게 맞긴 함.. 포인터로 넘겨줘야지
3. 맵에 데이터가 안들어가나? 코드로 넣어봄. => 코드로 넣으면 잘 들어감
4. 맵에 넣을때 깊은복사, 얕은복사 문제인가? => 맵에 넣을때는 pass by value 가 디폴트라고 나옴


그래서 뭐가 문제지?

*/