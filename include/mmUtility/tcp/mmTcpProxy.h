#pragma once

class TCPProxy
{
public:
    virtual void handleProcess(char*, unsigned int) = 0;
};