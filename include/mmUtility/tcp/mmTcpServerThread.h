#pragma once
#include "mmTcpServer.h"
class MUTILITY_DLLEXPORT mmTcpServerThread
{
public:
    mmTcpServerThread(unsigned short iPort);
    ~mmTcpServerThread();
public:
    void start();
    void stop();
    void restart();
protected:
    void handleEvent();
private:
    mmTcpServer m_server;
};

