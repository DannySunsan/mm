#include "boost/property_tree/ptree.hpp"

#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>  
using namespace std;
using namespace boost::property_tree;
int  loadConfig()
{
    ptree pt;
    read_xml("conf.xml", pt);     //读入一个xml文件
}