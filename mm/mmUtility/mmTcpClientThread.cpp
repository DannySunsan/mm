#include "mmUtility\tcp\mmTcpClientThread.h"

mmTcpClientThread::mmTcpClientThread()
{    
}
mmTcpClientThread::~mmTcpClientThread()
{

}

void mmTcpClientThread::Listen(const char* sIp, unsigned short iPort)
{
   /* boost::asio::ip::tcp::endpoint ep(boost::asio::ip::address::from_string(sIp), iPort);
    m_client = std::move(mmTcpClient(ep));*/
   
}

void mmTcpClientThread::Send(const char* str, unsigned int uLen)
{
  
}