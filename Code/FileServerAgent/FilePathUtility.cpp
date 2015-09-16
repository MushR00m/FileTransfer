#include <iostream>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include "FilePathUtility.h"
using namespace std;

void GetFileNameFromPath(std::string &path,std::string& filename)
{
	std::string strTag ="C:\\Users\\hao-yu\\Desktop\\Linux多线程服务端编程：使用muduo C++网络库.pdf";
	boost::char_separator<char> sep("\\");

	typedef boost::tokenizer<boost::char_separator<char>>CustonTokenizer;
	CustonTokenizer tok(path,sep);
	                                                                              
	std::vector<std::string> vecSegTag;
	

	CustonTokenizer::iterator beg=tok.begin();

	while (beg!=tok.end())
	{
		++beg;
	}
	for(CustonTokenizer::iterator beg=tok.begin(); beg!=tok.end();++beg)
	{
		vecSegTag.push_back(*beg);
	}
	filename=vecSegTag.back();
}