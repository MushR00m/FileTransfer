#pragma once

#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/thread.hpp>
#include "..\Protocol\Message.h"
#include "..\Protocol\RequestFileMessage.h"
#include "..\Protocol\WrtieFileMessage.h"
#include "..\Protocol\MessageFactory.h"
#include <iostream>


using namespace  boost;
using namespace  boost::asio;
using namespace boost::asio::ip;

class FileTrasferTask;
class DataPackage;
class Message;
#define max_len 268
using namespace protocol;
class Session:public enable_shared_from_this<Session>
{

private:
	static int session_id;

	static boost::mutex m_session_mu;

	static int getSessionId();

private:

	MessageFactory msgfactory_;

	//远端socket连接
	tcp::socket m_socket;

	//接受数据缓冲区
	boost::shared_array<unsigned char> m_recbuf;

	boost::shared_ptr<FileTrasferTask> m_ft_ptr;

	//解析互斥锁
	boost::mutex m_resolve_mu;

	char *temp;

	int sendbytes;
public:

	//会话ID
	int SessionId;

	Session(io_service & ios);

	Session(const Session &ses);

	~Session(void);

	//taskid
	void writedata(int taskid,DataPackage datapackage);

	tcp::socket& socket();

	//开始监听
	void start();

	void handle_write(const boost::system::error_code& error,size_t bytesnum);

	void handle_readHeader(const boost::system::error_code& error,std::size_t bytes_transferred);

	void handle_readBody(const boost::system::error_code& error,std::size_t bytes_transferred);

	void handle_readfile(const boost::system::error_code& error,std::size_t bytes_transferred);

	void ReceiveMessage(boost::shared_ptr<protocol::Message>& msg);

private:

	boost::shared_array<char> m_sendbuf;

	boost::shared_ptr<RequestFileMessage> msgrquestfile_;

	shared_ptr<FileTrasferTask> m_ftask_ptr;

	void ResolveData();
};

