#pragma once
#include <boost/asio.hpp>
#include <boost/function.hpp>
#include <boost/smart_ptr.hpp>
using namespace  boost;
using namespace boost::asio;

class Transfer
{
	//接受到客户端的连接
	function<void (shared_ptr<ip::tcp::socket> sock)> acceptclient;
	//客户端断开连接
	function<void(shared_ptr<ip::tcp::socket> sock)> clientdisconnect;
public:

	Transfer(void);

	~Transfer(void);

};

