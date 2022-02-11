#include "export.h"
#include "mmUtility\tcp\mmTcpClient.h"
#include <iostream>
#include "boost\thread.hpp"

mmTcpClient::mmTcpClient(TCPProxy* proxy)
{
    client_ = new mmTcpClientConnection(proxy);
    
}

void mmTcpClient::connect(const char* ip, unsigned short port)
{
    client_->connect(ip , port);
}

void mmTcpClient::close()
{
    client_->close();
}

void mmTcpClient::send(char* s, unsigned int len)
{
    TCPMsgHead pdata;

    std::string sip = client_->socket().local_endpoint().address().to_string();
    memcpy(pdata.s_ip, (char*)(sip.c_str()), sip.length());
    pdata.s_ip[sip.length()] = '\0';
    pdata.i_port = client_->socket().local_endpoint().port();
    pdata.s_cmd[0] = '1';
    pdata.s_cmd[1] = '\0';
    pdata.len = sizeof(TCPMsgHead) + len + 1;
    
    TCPData data;
    data.head = pdata;
    data.s = new char[len+1];
    memcpy(data.s,s,len);
    data.s[len] = '\0';
    client_->send((char*)&data, pdata.len);
}