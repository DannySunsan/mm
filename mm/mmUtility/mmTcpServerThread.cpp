#include "export.h"
#include "mmUtility\tcp\mmTcpServerThread.h"
#include "boost\thread.hpp"
mmTcpServerThread::mmTcpServerThread(unsigned short usPort)
    :m_server(usPort)
{
    start();
}

mmTcpServerThread::~mmTcpServerThread()
{
}

void mmTcpServerThread::start()
{
   boost::thread([this]() { 
        
       m_server.run();
        
        });  
}

void mmTcpServerThread::stop()
{
    m_server.stop();
}

void mmTcpServerThread::restart()
{
    m_server.restart();
}
