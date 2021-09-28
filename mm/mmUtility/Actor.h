#pragma once
class Actor
{
public:
    Actor();
    ~Actor();

    bool Start(void);
    bool Suspend(void);
    bool Resume(void);
};

