#include "OrderProcessor.h"
#include "RequestReceiver.h"
#include <vector>
using namespace std;




RequestReceiver::RequestReceiver() 
{
    orderProcessor = new OrderProcessor;
}

RequestReceiver::~RequestReceiver()
{
    delete orderProcessor;
}

OrderRequest RequestReceiver::CallOrderProcessor(OrderRequest _orderRequest)
{
    
}

void RequestReceiver::receiveReq(OrderRequest req)
{
    //proceedRequest p;
    //p.process();
    
    cout << "pos" << endl;
    orderProcessor->process(req);

    //ProceedRequest::getInstance()->process(req);
}



// OrderRequest 정보를 넘겨서 ProceedRequest 처리 하기 직전까지 생각
