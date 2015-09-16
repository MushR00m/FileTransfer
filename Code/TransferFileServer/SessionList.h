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

	//�Ự�б�
	std::map<int,boost::shared_ptr<Session>> m_smap;

	//readsession lock
	boost::mutex m_mutex;
public:

	//ȡ�õ�һʵ��
	static SessionList* getInstance(){return m_instance;}

	//��ʼ���Ự�б�
	static void Init();

	//����session id
	UINT insert(boost::shared_ptr<ip::tcp::socket> usr);

	//���ݻỰ���ҵ�session
	boost::shared_ptr<Session> findSessionById(UINT id);
};

