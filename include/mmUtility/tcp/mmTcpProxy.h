#pragma once
#include "common\mm_define.h"

BEGIN_NAMESPACE_MM
class TCPProxy
{
public:
    virtual void handleProcess(char*, unsigned int) = 0;
};
END_NAMESPACE_MM