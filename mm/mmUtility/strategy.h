#pragma once
#include "RefCounterPtr.h"
class strategy
{
public:
   virtual strategy* createStrategy() = 0;
};
class strategyContext
{
public:
    virtual void dealWithStrategy() = 0;
private:
    strategy* m_strategy;
};