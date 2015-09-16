#pragma once
#include <map>
#include <boost/smart_ptr.hpp>
#include <boost/thread.hpp>
#include <boost/asio.hpp>

class Session;

using namespace  boost;
using namespace boost::asio;

class SessionList
{
private:
	SessionList(void);

	~SessionList(void);

	static SessionList * m_instance;

	//会话列表
	std::map<int,boost::shared_ptr<Session>> m_smap;

	//readsession lock
	boost::mutex m_mutex;
public:

	//取得单一实例
	static SessionList* getInstance(){return m_instance;}

	//初始化会话列表
	static void Init();

	//返回session id
	UINT insert(boost::shared_ptr<ip::tcp::socket> usr);

	//根据会话查找到session
	boost::shared_ptr<Session> findSessionById(UINT id);
};

