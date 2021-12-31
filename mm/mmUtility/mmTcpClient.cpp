#include "export.h"
#include "mmUtility\tcp\mmTcpClient.h"
#include <iostream>
mmTcpClient::mmTcpClient()
{

}
void mmTcpClient::connect(const char* ip, unsigned short port)
{
    if (client.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip), port)))
    {
        std::cout << "connect to :" << ip << "ok\n";
    }
    else
    {
        std::cout << "connect to :" << ip << "failure\n";
    }
}

void mmTcpClient::send(char* s, int len)
{
    client.send(s,len);
}

void mmTcpClient::send(const char* s)
{
    client.send(s);
}

void mmTcpClient::receive()
{
    client.receive();
}