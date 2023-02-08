#include <map>
#include <string>
#include <iostream>
#include "TradeDef.h"

using namespace std;

class UserDataHandler
{
public:
    UserDataHandler();
    ~UserDataHandler();

private:
    map<string, User>UserDataMap; // <UserId, User>
};


