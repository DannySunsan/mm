#pragma once
#include "common\mm_define.h"
#include <memory>
BEGIN_NAMESPACE_MM
enum eTcpStatus
{
    STATUS_UNPREPARED = -1,
    STATUS_OK = 0,
    STATUS_ERROR_INIT_FAILURE,
};
enum eDataType
{
    eint32,
    eint64,
    efloat,
    edouble,
    estring,
    ewstring
};

enum eStateReceive
{
    start = 0,
    receiving,
    end
};
#pragma pack(1)
typedef struct
{
    char s_ip[32];
    int16_t i_port;
    char s_cmd[128];
    unsigned int len;
}TCPMsgHead,*TCPMsgHeadP;
typedef struct TCPDATA
{
    TCPMsgHead head;
    char* s;
    TCPDATA()
    {
        memset(&head,0,sizeof(TCPMsgHead));
        s = nullptr;
    }
}TCPData;
struct DataFormat
{
    eStateReceive state;
    TCPMsgHead head;
    DataFormat()
    {
        state = start;
        memset(&head,0,sizeof(TCPMsgHead));
    }
};
#pragma pack()

#define SENDSIZE        1024
END_NAMESPACE_MM