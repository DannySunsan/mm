#include "boost/any.hpp"
#include "boost/regex.hpp"
#include <boost/tokenizer.hpp> 
#include "boost/lexical_cast.hpp"

#include <vector>
#include <iostream>
#include "mmUtility/CmmUtility.h"

#include "mmUtility/hashMap.h"
#include "ThreadPool.h"
//#include <thread>
void testAny();
void teststr();
std::vector<int> twoSum(std::vector<int>& nums, int target);

namespace std {
    class Solution {
    public:
        vector<int> getLeastNumbers(vector<int>& arr, int k) {
            //c++¥Û∂•∂—
            //make_heap(arr.begin(), arr.end(), less<int>());
            //c++–°∂•∂—
            //make_heap(arr.begin(), arr.end(), greater<int>());
            //pop_heap(arr.begin(), arr.end());

            priority_queue<int, vector<int>,greater<int>> pq;
            for (auto a : arr)
                pq.push(a);

            vector<int> vecRet;
            for (int i = 0; i < k; i++)
            {
                vecRet.emplace_back(pq.top());
                pq.pop();               
            }
            return vecRet;
        }
    };
}
template <class _Arg, class _Result>
struct unary_function {
    typedef _Arg argument_type;
    typedef _Result result_type;

    result_type operator()(argument_type&& ar)
    {
        return static_cast<result_type>(ar * 5);
    }
};

bool hasA()
{
    return true;
}
void CmmUtility::test()
{
    std::vector<int> nums = { 3,2,4,7,2,1 };
    std::vector<int> vctRet/* = twoSum(nums,6)*/;
    if (1 || hasA())
    {
        
    }
   /* std::cout << "this is test function\n";
    testAny();
    teststr();*/
   /* std::Solution so;
    vctRet = so.getLeastNumbers(nums,2);*/

   /* ThreadPool pool(3);
    for (int i=0;i<10;i++)
    {
        auto pi = pool.enqueue([i] {
            std::cout << std::this_thread::get_id() <<"  add a task:" << i << std::endl;
            });
    }
    Sleep(1000);
    for (int i = 0; i < 10; i++)
    {
        auto pi = pool.enqueue([i] {
            std::cout << std::this_thread::get_id() << "  add a task:" << i << std::endl;
            });
    }*/
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
    std::string sI = "5";
    try
    {
        int i = boost::lexical_cast<int>(sI);
    }
    catch (boost::bad_lexical_cast e)
    {
        std::cout << e.what() << std::endl;
    }
}

void testFakeFun()
{
    unary_function<int, int> p;
    int ret = p(3);
    std::cout << ret <<std::endl;
}
std::vector<int> twoSum(std::vector<int>& nums, int target)
{
    std::multimap<int, int> mapNums;
    int index = 0;
    for (int i : nums)
    {
        mapNums.insert(std::make_pair(i, index++));
    }
    for (int i = 0; i < nums.size(); i++)
    {
        int j = target - nums[i];
        auto itFind = mapNums.find(j);
        int nSize = mapNums.count(j);
        for (; nSize > 0; nSize--, itFind++)
        {
            if (itFind->second == i)
                continue;
            return { i,itFind->second };
        }
    }
    return {};
}

bool isIsomorphic(std::string s, std::string t) 
{
    //÷ª≈–∂œ÷ÿ∏¥

    return true;
}

