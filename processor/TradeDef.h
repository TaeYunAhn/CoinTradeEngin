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