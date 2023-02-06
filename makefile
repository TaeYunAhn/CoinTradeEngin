CC=g++
CFLAGS=-g -Wall
OBJS=main.o state/WorkerState.o state/StateHandler.o state/FinalState.o processor/OrderBookHandler.o processor/OrderProcessor.o processor/RequestReceiver.o processor/ResponseSender.o
TARGET=CoinTradeEngine.out
 
all: $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -o $@ $(OBJS)
