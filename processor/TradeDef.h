#pragma once
#include <string>


using namespace std;

enum OrderType
{
    EN_MARKET,
    EN_LIMIT,
};

enum Side
{
    EN_BUY,
    EN_SELL,
};

class TradeDataUtil
{
public:
    static std::string getSideStr(const Side& side)
    {
        switch (side)
        {
        case EN_BUY: return "EN_BUY";
        case EN_SELL: return "EN_SELL";
        default: return "";
        }
    }
};


enum class OrderBookErrorMessage
{
    EN_NOT_ENOUGH_QTY,
    EN_NOT_MATCHED_PRICE,
    EN_NOT_ENOUGH_BALANCE,
    EN_GET_ENOUTH_QTY,
    EN_CONCLUSION_SUCCESS,
};

enum class ProcessorErrorMessage
{
    EN_WRONG_PRICE,
    EN_WRONG_QTY,
    EN_NOT_ENOUGH_BALANCE,
    EN_CHECK_ORDER_SUCCESS,
};

struct OrderRequest
{
    string symbol;
    double price;
    double qty;
    Side side;
    OrderType orderType;
    string requestId;
    string userId;
    time_t time;

    OrderRequest() {}
    OrderRequest(OrderType input_orderType, string input_symbol, Side input_side, double input_price, double input_qty)
    {
        orderType = input_orderType;
        symbol = input_symbol;
        side = input_side;
        price = input_price;
        qty = input_qty;
    }
};



struct Order
{
    string symbol;
    double price;
    double qty;
    Side side;
    string orderId;
    string userId;
    time_t time;
};

struct Wallet
{
    string coinName;
    double qty;
};

struct User
{
    string userId;
    string userEmail;
    double balance;      // 잔액
    double margin;       // 총 매수
    double evaluation;   // 총 평가 (총 매수 + 평가손익)
    double assets;       // 총 보유자산 (잔액 + 총 평가)
    double profit;       // 평가손익
    double profitRate;   // 수익률
    Order order;
    Wallet wallet;
    //Position position;
};




struct Position
{
    string symbol;
    double price;
    double qty;
    Side side;
    string orderId;
    string userId;
    time_t time;
    double PL;
    double margin;
};

//struct OrderResponse
//{
//
//};