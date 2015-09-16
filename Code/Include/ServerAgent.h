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
	//�����ⲿ�Ļص�����
	FileSendPercent m_percentCall;

    io_service m_ios;

	ip::tcp::endpoint m_endpoint;

	//���ӷ���˵�socket
	ip::tcp::socket m_sock;

	boost::shared_array<char> m_sendbuf;



	//�ļ����͹�������
	void FileSending(std::string filename);

	//���ӷ�����
	void ConnectServer();

	//��������Ͽ�����
	void Disconnect();

	//�����ļ�����
	int m_sendtimes;

	//�����ٶ�ÿ������ֽ�
	int m_Speed;
	//�Ѿ����͵��ֽ���
	int m_SendedBytes;
	bool m_Sending;
public:
	ServerAgent(std::string &serveraddr,short &port);

	~ServerAgent(void);

	//�����ļ�
	void SendFile(std::string &filename,FileSendPercent & filesendpercent);

	
	void SpeedCall();


	

};

