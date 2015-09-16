#pragma once
#include <iostream>
#include <boost/function.hpp>
#include  <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/smart_ptr.hpp>
#ifdef _DLL_FileServerAgent
#define DLL_ServerAgent_API __declspec(dllexport)
#else
#define DLL_ServerAgent_API __declspec(dllimport)
#pragma comment(lib,"FileServerAgent.lib")
#endif

typedef boost::function<void(float)> FileSendPercent; 

using namespace  boost;
using namespace  boost::asio;

class DLL_ServerAgent_API ServerAgent
{
private:
	//调用外部的回调方法
	FileSendPercent m_percentCall;

    io_service m_ios;

	ip::tcp::endpoint m_endpoint;

	//连接服务端的socket
	ip::tcp::socket m_sock;

	boost::shared_array<char> m_sendbuf;



	//文件发送工作方法
	void FileSending(std::string filename);

	//连接服务器
	void ConnectServer();

	//与服务器断开连接
	void Disconnect();

	//发送文件次数
	int m_sendtimes;

	//传输速度每秒多少字节
	int m_Speed;
	//已经发送的字节数
	int m_SendedBytes;
	bool m_Sending;
public:
	ServerAgent(std::string &serveraddr,short &port);

	~ServerAgent(void);

	//发送文件
	void SendFile(std::string &filename,FileSendPercent & filesendpercent);

	
	void SpeedCall();


	

};

