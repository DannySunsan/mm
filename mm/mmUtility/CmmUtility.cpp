#include "boost/any.hpp"
#include <list>
#include <iostream>
#include "mmUtility/util.h"

void CmmUtility::test()
{
    std::cout << "this is test function\n";

    std::list<boost::any> listAny;

    listAny.emplace_back(1);
    listAny.emplace_back("123");
    int iNum[] = { 55,16 };
    listAny.emplace_back(iNum);

    //auto itor = listAny.begin();
    //std::cout<< static_cast<int>(*itor) <<
}