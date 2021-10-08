#pragma once
#include "export.h"
#include <vector>
class MUTILITY_DLLEXPORT CmmUtility
{
public:
    static void test();
    static int splitString(const std::string& strSrc,std::vector<std::string>& vecRet,char c = ' ');
};