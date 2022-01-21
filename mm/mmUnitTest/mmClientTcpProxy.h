#pragma once
#include "mmUtility\tcp\mmTcpProxy.h"

class mmClientTcpProxy :public TCPProxy
{
public:
    virtual void handleProcess(char*, unsigned int);
};