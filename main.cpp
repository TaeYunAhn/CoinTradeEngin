#include <unistd.h>
#include <sys/signal.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include "./state/StateHandler.h"

using namespace std;

const char* getSignalStr(int signo)
{
    switch (signo)
    {
    case SIGUSR1: return "SIGUSR1";
    case SIGTERM: return "SIGTERM";
    case SIGSEGV: return "SIGSEGV";
    case SIGINT: return "SIGINT";
    case SIGABRT: return "SIGABRT";
    }

   return "NONE";
}

static void signal_handler(int sig) 
{

    //ConnectorPool::getInstance()->shutdown();
}

int main(int argc, char* argv[])
{
   //if( argc != 2 ) 
   //{
   //   stringstream ss;
   //   ss << "[ERROR](" << __FILE__ << ", " << __LINE__ <<") " << "Usage: " << argv[0] << " <conf file path>" << endl;
   //   cerr << ss.str() << endl;
   //   return 0;
   //}

    
   //CSettings::getInstance()->reconstructSettings(argv[1]);

    pid_t pid;

   if( (pid = fork()) < 0 ) 
   {
      ostringstream ss;
      ss << "[ERROR](" << __FILE__ << ", " << __LINE__ <<") " << "Can't Fork" << endl;
      cerr << ss.str() << endl;
      exit(errno);
   }
   else if( pid != 0 )
      exit(0);

    if (signal(SIGUSR1, signal_handler) == SIG_ERR || signal(SIGTERM, signal_handler) == SIG_ERR || signal(SIGSEGV, signal_handler) == SIG_ERR || signal(SIGINT, signal_handler) == SIG_ERR )
   {
      ostringstream ss;
      ss << "[ERROR](" << __FILE__ << ", " << __LINE__ <<") " << "Can't Set Signal Handler" << endl;
      return 0;
   }

   ofstream pidFile("/home/tahn/code_trade_engine/pid", ios_base::trunc);
   
   if( pidFile.fail()) 
   {
      ostringstream ss;
      ss << "[ERROR](" << __FILE__ << ", " << __LINE__ <<") " << "Can't Open PID File: " << endl;
      cerr << ss.str();
      return 0;
   }
   else 
   {
      pidFile << getpid();
      pidFile.close();
   }
   std::cout << "pidFile finish"<<endl;
   StateHandler stateHandler;
   stateHandler.proceed();
   
    return 0;
}