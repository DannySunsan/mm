#pragma once

class mmTcpServerTransaction
{
    mmTcpServerTransaction();
    virtual ~mmTcpServerTransaction();
    virtual void receive(char* s, unsigned int len) = 0;
};