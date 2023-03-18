#pragma once
#include <map>
#include <iostream>

struct OrderBook
{
    double price;
    double qty;
    double totalQty;
};

/*
* Request 진입 및 데이터 파싱
* Request 체크 후 Order & Position 진행
* Account 반영
* 전체 정보 반영
* Response 보내기 <- UI 에 따라 달라질듯
*/

std::map<double, QtyData> BUY_map; // 키 : 가격, 밸류 : 갯수
std::map<double, QtyData> SELL_map;