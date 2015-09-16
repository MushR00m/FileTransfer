#include "stdafx.h"
#define _DLL_FileServerAgent
#include <fstream>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include <atlfile.h>
#include <atlstr.h>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>


#include "ServerAgent.h"
#include "FilePathUtility.h"
#include "..\Protocol\Message.h"
#include "..\Protocol\RequestFileMessage.h"
#include "..\Protocol\WrtieFileMessage.h"


using namespace protocol;

ServerAgent::ServerAgent(std::string &serveraddr,short &port):m_ios(),
	m_sock(m_ios),
	m_endpoint(ip::address::from_string(serveraddr),port),
	m_Sending(false),
	m_SendedBytes(0)
{

}

ServerAgent::~ServerAgent(void)
{

}



void ServerAgent::SendFile(std::string &filename,FileSendPercent & filesendpercent)
{
	m_percentCall=filesendpercent;
	m_Sending=true;
	boost::thread timethread(boost::bind(&ServerAgent::SpeedCall,this));
	boost::thread thread(boost::bind(&ServerAgent::FileSending,this,std::string(filename)));
	thread.join();
}

enum Msgoffset
{
	headeroffset=0,
	typeoffset=4,
	filenamelenoffset=8,
	filenameoffset=12,
	sendtimesoffset=4
};

void ServerAgent::FileSending(std::string filepath)
{
	int msglen=0;
	int requesttype=0;
	string filename;
	GetFileNameFromPath(filepath,filename);


	int times=10;//传输次数
	RequestFileMessage rqmsg;
	rqmsg.Filename=filename;

	CString pathstr(filepath.data());
	CAtlFile file;
	HRESULT r=file.Create(pathstr,GENERIC_READ | GENERIC_WRITE, 0, OPEN_EXISTING);
	if (FAILED(r))
	{
		std::cout<<"文件打开错误"<<std::endl;
	}
	ULONGLONG filesize;

	if(FAILED(file.GetSize(filesize)))
	{
		std::cout<<"获取文件大小错误"<<std::endl;
	}
	std::cout<<"文件"<<filepath<<"大小"<<filesize<<std::endl;

	times=filesize/packagelen;//计算出要发送的次数

	if ((filesize%packagelen)>0)
	{
		times++;
	}
	m_sendtimes=times;
	std::cout<<"文件需要发送次数"<<m_sendtimes<<std::endl;
	rqmsg.TransferTimes=times;


	MessageData rqmsgdata=rqmsg.GetBytes();
	ConnectServer();//连接服务器
	boost::system::error_code sendec,recvec;
	boost::shared_array<char> recbuf(new char[100]);

	std::size_t rec_num=m_sock.receive(boost::asio::buffer(recbuf.get(),100));//先接受4字节的数据
	m_sock.send(boost::asio::buffer(rqmsgdata.buf.get(),rqmsgdata.buflen));

	m_sock.receive(boost::asio::buffer(recbuf.get(),100));

	WrtieFileMessage writefilemsg;
	writefilemsg.packagebytesnum=packagelen;//设定上每包数据的数据量
	
	for (int i=0;i<m_sendtimes;i++)
	{
		writefilemsg.packagenum=i;
		if (i==(m_sendtimes-1))
		{
			if (filesize%packagelen>0)
			{
				writefilemsg.packagebytesnum=filesize%packagelen;
				MessageData data=writefilemsg.GetBytes();
				file.Read(data.buf.get()+MSGHEADLEN+WriteFileMessagelen,writefilemsg.packagebytesnum);
				m_sock.send(boost::asio::buffer(data.buf.get(),data.buflen));
				m_SendedBytes+=writefilemsg.packagebytesnum;
			}
			else
			{
				MessageData data=writefilemsg.GetBytes();
				file.Read(data.buf.get()+MSGHEADLEN+WriteFileMessagelen,packagelen);
				m_sock.send(boost::asio::buffer(data.buf.get(),data.buflen));
				m_SendedBytes+=packagelen;
			}
		}
		else
		{
			MessageData data=writefilemsg.GetBytes();
			file.Read(data.buf.get()+MSGHEADLEN+WriteFileMessagelen,packagelen);
			m_sock.send(boost::asio::buffer(data.buf.get(),data.buflen));
			m_SendedBytes+=packagelen;
		}
		rec_num=m_sock.receive(boost::asio::buffer(recbuf.get(),100));
	}
	m_Sending=false;
}

void ServerAgent::ConnectServer()
{
	std::cout<<"Enter ServerAgent::ConnectServer"<<std::endl;
	m_sock.connect(m_endpoint);
	std::cout<<"Exit ServerAgent::ConnectServer"<<std::endl;
}

void ServerAgent::Disconnect()
{
	std::cout<<"Enter ServerAgent::Disconnect"<<std::endl;
	m_sock.close();
	std::cout<<"Exit ServerAgent::Disconnect"<<std::endl;
}

void ServerAgent::SpeedCall()
{
  using namespace boost::asio;
  asio::io_service ios;
  while (m_Sending)
  {
	  asio::deadline_timer t(ios, boost::posix_time::seconds(1));
	  t.wait();
	  int sendbytes=m_SendedBytes/(1024*1024);
	  std::cout<<"每秒发送"<<sendbytes<<std::endl;
	 m_SendedBytes=0;
  }
}
