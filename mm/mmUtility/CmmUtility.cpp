#include "boost/any.hpp"
#include "boost/regex.hpp"
#include "boost/tokenizer.hpp"
#include "boost/lexical_cast.hpp"
#include "boost\date_time.hpp"
#include <vector>
#include <iostream>
#include "mmUtility/CmmUtility.h"

#include "mmUtility/hashMap.h"
//#include <thread>

std::vector<std::string> reg(std::string s, std::string pattern, int nStart = 0)
{
    auto res = std::vector<std::string>();
    boost::regex r(pattern);
    boost::sregex_iterator pos(s.cbegin(), s.cend(), r), end;
    for (; pos != end; ++pos)
        res.push_back(pos->str(nStart));
    return res;
}

void CmmUtility::test()
{

}
int CmmUtility::splitString(const std::string& strSrc, std::vector<std::string>& vecRet, char c)
{
    vecRet.clear();
    typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
    boost::char_separator<char> sep(&c);
    
    tokenizer tok(strSrc, sep);
    for (tokenizer::iterator it = tok.begin(); it != tok.end(); ++it)
    {
        vecRet.emplace_back(*it);
    }
    return vecRet.size();
}

void CmmUtility::splitFunc(const std::string& strSrc, std::vector<std::string>& vecStr, std::vector<int>& vecNum)
{
    std::string fm1("(?<=\\[)(\\d+)(?=\\])");
    boost::smatch what;

    for (auto s : reg(strSrc, fm1))
    {
        vecNum.emplace_back(atoi(s.c_str()));
    }
        
    std::string fm2("(?<=\")[a-z]+(?=\")");
    vecStr = reg(strSrc, fm2);
}
std::string CmmUtility::make_daytime_string()
{
    return boost::posix_time::to_iso_extended_string(boost::posix_time::second_clock::local_time());
}
