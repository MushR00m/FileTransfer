#pragma once
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>
using namespace  boost;
using namespace boost::asio;

class Transfer
{
	//���ܵ��ͻ��˵�����
	function<void (shared_ptr<ip::tcp::socket> sock)> acceptclient;
	//�ͻ��˶Ͽ�����
	function<void(shared_ptr<ip::tcp::socket> sock)> clientdisconnect;
public:

	Transfer(void);

	~Transfer(void);

};

