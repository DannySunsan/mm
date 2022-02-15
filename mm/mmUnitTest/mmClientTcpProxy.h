#pragma once
#include "mmUtility\tcp\mmTcpProxy.h"
BEGIN_NAMESPACE_MM
class mmClientTcpProxy :public TCPProxy
{
public:
    virtual void handleProcess(char*, unsigned int);
};
END_NAMESPACE_MM