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

	//线程组
	boost::thread_group m_threadgroup;
  
public:

	static ServerManage* GetInstance();
	
	//启动开始接受链接
	static void start();

	//二段式初始化
	static void Init();

	static void Run();

	//用户登录
	void OnUserConnect(shared_ptr<Session>& sess_ptr,const boost::system::error_code& error);

	//用户断开连接
	void OnUserDisconnect(shared_ptr<ip::tcp::socket> usr);
};

