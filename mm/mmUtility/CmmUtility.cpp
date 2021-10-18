#include "boost/any.hpp"
#include "boost/regex.hpp"
#include <boost/tokenizer.hpp> 

#include <vector>
#include <iostream>
#include "mmUtility/CmmUtility.h"
void testAny();
void teststr();

template <class _Arg, class _Result>
struct unary_function {
    typedef _Arg argument_type;
    typedef _Result result_type;

    result_type operator()(argument_type&& ar)
    {
        return static_cast<result_type>(ar * 5);
    }
};

void CmmUtility::test()
{
    std::cout << "this is test function\n";
    testAny();
    teststr();
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
std::vector<std::string> reg(std::string s, std::string pattern,int nStart=0)
{
    auto res = std::vector<std::string>();
    boost::regex r(pattern);
    boost::sregex_iterator pos(s.cbegin(), s.cend(), r), end;
    for (; pos != end; ++pos)
        res.push_back(pos->str(nStart));
    return res;
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

void testAny()
{
    std::vector<boost::any> vecAny;

    vecAny.emplace_back(1);
    vecAny.emplace_back(std::string("123"));
    std::vector<int> v = { 1, 2, 3 };
    vecAny.emplace_back(v);
    {
        try
        {
            std::cout << boost::any_cast<int>(vecAny[0]) << std::endl;
            std::cout << boost::any_cast<std::string>(vecAny[1]) << std::endl;
            std::vector<int> v2 = boost::any_cast<std::vector<int>>(vecAny[2]);
            std::cout << v2[0] << v2[1] << std::endl;
        }
        catch (boost::bad_any_cast& e)
        {
            std::cerr << e.what() << std::endl;
        }
    }
}
void teststr()
{
 
}

void testFakeFun()
{
    unary_function<int, int> p;
    int ret = p(3);
    std::cout << ret <<std::endl;
}