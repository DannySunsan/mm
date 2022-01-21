#include "export.h"
#include "mmUtility\tcp\mmTcpServerThread.h"
#include "boost\thread.hpp"
mmTcpServerThread::mmTcpServerThread(unsigned short usPort, TCPProxy* proxy)
    :server(usPort,proxy)
{
    start();
}

mmTcpServerThread::~mmTcpServerThread()
{
    server.stop();
}

void mmTcpServerThread::start()
{
   boost::thread([this]() { 
        
       server.run();
        
        }); 
 /*  boost::thread([this]() {
       for (;;)
       {
           server.start_accept();
       }      
       });*/
}

void mmTcpServerThread::write(std::string ip, char* s, unsigned int len)
{

    server.getConnection(ip)->write( s, len);
}