#include "boost/any.hpp"
#include <vector>
#include <iostream>
#include "mmUtility/util.h"

void CmmUtility::test()
{
    std::cout << "this is test function\n";

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