#pragma once
#include <fstream>
#include <boost/smart_ptr.hpp>
#include <boost/utility.hpp>
#include <atlfile.h>
class FileTrasferTask:public boost::noncopyable
{

	//std::fstream m_file;
	CAtlFile m_file;
public:

	FileTrasferTask(void);

	~FileTrasferTask(void);

	//�ļ���Ҫ�������
	int transfertimes;

	void Start(std::string filename);

	void WriteBytes(const char * buf,std::size_t bufsize);

	void Finish();

};

