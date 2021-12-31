#pragma once
#include "mmTcpConnection.h"
class MUTILITY_DLLEXPORT mmTcpClient
{
public:
    mmTcpClient();
    void connect(const char * ip,unsigned short port);
    void send(char * s,int len);
    void send(const char* s);
    void receive();
private:
    mmTcpClientConnection client;
};