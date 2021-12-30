#pragma once
#include "CmmUtility.h"
#include "hashtable.h"
#include "tcp\mmTcpClientThread.h"
#include "tcp\mmTcpServerThread.h"
#ifndef MDebug
#pragma comment(lib,"mmUtility.lib")
#else
#pragma comment(lib,"mmUtilityD.lib")
#endif // !MDebug

