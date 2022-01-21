#include "export.h"
#include "mmUtility\tcp\mmTcpClient.h"
#include <iostream>
#include "boost\thread.hpp"
mmTcpClient::mmTcpClient(TCPProxy* proxy):
    client(proxy)
{

}

void mmTcpClient::connect(const char* ip, unsigned short port)
{
    if (client.connect(boost::asio::ip::tcp::endpoint(boost::asio::ip::make_address(ip), port)))
    {
        std::cout << "connect to :" << ip << ",ok\n"; 
        init();
    }
    else
    {
        std::cout << "connect to :" << ip << "failure\n";
    }
}

void mmTcpClient::init()
{
    boost::thread([this]() {
        for (;;)
        {
            client.read();
        }     

        });
}

void mmTcpClient::send(char* s, unsigned int len)
{
    TCPData dataRet;
    std::string sip = client.socket().local_endpoint().address().to_string();
    memcpy(dataRet.head.s_ip, (char*)(&sip), sip.length());    
    dataRet.head.i_port = client.socket().local_endpoint().port();
    dataRet.head.len = sizeof(TCPMsgHead) + len;
    dataRet.s = s;
    
    client.send((char*)& dataRet, dataRet.head.len);
}