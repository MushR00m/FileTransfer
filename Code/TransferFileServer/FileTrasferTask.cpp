#include "stdafx.h"
#include "FileTrasferTask.h"
#include <iostream>
#include <boost/format.hpp>
#include <atlstr.h>
FileTrasferTask::FileTrasferTask(void):transfertimes(0)
{
}

FileTrasferTask::~FileTrasferTask(void)
{
}

void FileTrasferTask::WriteBytes(const char * buf,std::size_t bufsize)
{	
	m_file.Write(buf,bufsize);
	transfertimes++;
	std::cout<<"FileTrasferTask::WriteBytes"<<bufsize<<
		"transfertimes:"<<transfertimes<<std::endl;
}

void FileTrasferTask::Start(std::string filename)
{
	std::cout<<"创建输出文件"<<filename<<std::endl;
	CString cfilename(filename.c_str());
	HRESULT hr=m_file.Create(cfilename,GENERIC_WRITE, 0, CREATE_ALWAYS);
	if(FAILED(hr)){
		std::cout<<"打开文件错误"<<std::endl;
	} 
}

void FileTrasferTask::Finish()
{
	std::cout<<"FileTrasferTask::Finish"<<std::endl;
	m_file.Flush();
	m_file.Close();
}
