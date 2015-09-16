#pragma once

#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/thread.hpp>

using namespace boost::asio;
using namespace boost;
using namespace boost::asio::ip;


class Session;

class ServerManage
{
    io_service  ios_;

	tcp::acceptor acceptor_;

private:
	static ServerManage* m_Instance;

	ServerManage();

	ServerManage(const ServerManage& );

	~ServerManage(void);

	//�߳���
	boost::thread_group m_threadgroup;
  
public:

	static ServerManage* GetInstance();
	
	//������ʼ��������
	static void start();

	//����ʽ��ʼ��
	static void Init();

	static void Run();

	//�û���¼
	void OnUserConnect(shared_ptr<Session>& sess_ptr,const boost::system::error_code& error);

	//�û��Ͽ�����
	void OnUserDisconnect(shared_ptr<ip::tcp::socket> usr);
};

