#pragma once
#include "export.h"
#include <vector>
#include "mmUtility/hashtable.h"
#include <string>
class MUTILITY_DLLEXPORT CmmUtility
{
public:
    static void test();
    static int splitString(const std::string& strSrc,std::vector<std::string>& vecRet,char c = ' ');
    static void splitFunc(const std::string& strSrc, std::vector<std::string>& vecStr, std::vector<int>& vecNum);
    static std::string make_daytime_string();
};