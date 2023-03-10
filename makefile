CC=g++
CFLAGS=-g -Wall
OBJS=main.o state/WorkerState.o state/StateHandler.o state/FinalState.o processor/OrderBookHandler.o processor/OrderProcessor.o processor/RequestReceiver.o processor/ResponseSender.o processor/UserDataHandler.o 
TARGET=CoinTradeEngine.out
 
all: $(TARGET)

clean:
	rm -f *.o
	rm -f */*.o
	rm -f $(TARGET)

$(TARGET): $(OBJS)
	$(CC) -g -o  $@ $(OBJS)

.SUFFIXES: .o .cpp
.cpp.o:
	$(CC) $(CFLAGS) -g -c -O0 -o $@ $<
