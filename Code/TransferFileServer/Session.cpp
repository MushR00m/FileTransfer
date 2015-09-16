#include "stdafx.h"
#include "Session.h"
#include <iostream>
#include <boost/smart_ptr.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include "FileTrasferTask.h"

int Session::session_id=0; //初始化sessionid为0

boost::mutex Session::m_session_mu;
#define sendbuflen (100)

Session::Session(io_service & ios):msgfactory_(),
	m_socket(ios),
	sendbytes(0),
	m_sendbuf(new char[sendbuflen])
{
	msgfactory_.ResolveMessage=boost::bind(&Session::ReceiveMessage,this,_1);
	temp=new char[1024];
	memset(temp,0x00,1024);
}

Session::~Session(void)
{
	std::cout<<"session被析构"<<std::endl;
}

tcp::socket& Session::socket()
{
	return m_socket;
}

void Session::handle_write(const boost::system::error_code& error,size_t bytesnum)
{
	if (!error)
	{
		std::cout<<"Session::handle_write"<<"发送给客户端字节数量"<<bytesnum<<std::endl;	
	}
	else
	{
		std::cout<<error.message()<<std::endl;
	}
}

void Session::handle_readHeader(const boost::system::error_code& error,std::size_t bytes_transferred )
{
	boost::mutex::scoped_lock lock(m_resolve_mu);
	if(!error)
	{
	     std::cout<<"解析协议头 传输字节数量"<<bytes_transferred<<std::endl;
		 msgfactory_.HandleMessage(bytes_transferred);
		 m_socket.async_receive(boost::asio::buffer(msgfactory_.GetMessageBuf(),msgfactory_.GetMessageBufLen()),
			 boost::bind(&Session::handle_readHeader,shared_from_this(),
			 boost::asio::placeholders::error,placeholders::bytes_transferred));
	}
	else
	{
		std::cout<<error.message()<<std::endl;
		std::cout<<"传输字节数量为"<<bytes_transferred<<std::endl;
	}
}

void Session::start()
{
	SessionId=getSessionId();
	m_socket.async_send(boost::asio::buffer(&SessionId,4),
		bind(&Session::handle_write,
		shared_from_this(),
		boost::asio::placeholders::error,
		placeholders::bytes_transferred));
	m_socket.async_receive(boost::asio::buffer(msgfactory_.GetMessageBuf(),msgfactory_.GetMessageBufLen()),
			boost::bind(&Session::handle_readHeader,shared_from_this(),
			boost::asio::placeholders::error,placeholders::bytes_transferred));
}

void Session::ResolveData()
{
	std::cout<<"Session::ResolveData"<<std::endl;
}

void Session::handle_readBody(const boost::system::error_code& error,std::size_t bytes_transferred)
{
}

void Session::handle_readfile(const boost::system::error_code& error,std::size_t bytes_transferred)
{
}

int Session::getSessionId()
{
	boost::mutex::scoped_lock sl(m_session_mu);
	session_id++;
	return session_id;
}

void Session::ReceiveMessage(boost::shared_ptr<protocol::Message>& msg)
{
	
	switch (msg->msgtype_)
	{
	case msg_RequestSendFile:
		{
			boost::shared_ptr<protocol::RequestFileMessage> rmsg=boost::static_pointer_cast<protocol::RequestFileMessage>(msg);
			msgrquestfile_=rmsg;
			std::cout<<"filename"<<rmsg->Filename<<std::endl;
			std::cout<<"filesize"<<rmsg->FileSize<<std::endl;
			m_ftask_ptr=shared_ptr<FileTrasferTask>(new FileTrasferTask());
			m_ftask_ptr->Start(rmsg->Filename);
			std::cout<<"Session::ResolveData"<<"消息类型为:msg_RequestSendFile"<<std::endl;
			m_socket.async_send(boost::asio::buffer(m_sendbuf.get(),4),
				bind(&Session::handle_write,
				shared_from_this(),
				boost::asio::placeholders::error,
				placeholders::bytes_transferred));
		}
		break;
	case msg_WriteFile:
		{
			boost::shared_ptr<protocol::WrtieFileMessage> wmsg=boost::static_pointer_cast<protocol::WrtieFileMessage>(msg);
			std::cout<<"Session::ResolveData"<<"消息类型为:msg_WriteFile"<<std::endl;
			m_ftask_ptr->WriteBytes(wmsg->GetData(),wmsg->GetDataLen());
			m_socket.async_send(boost::asio::buffer(&m_ftask_ptr->transfertimes,4),
				bind(&Session::handle_write,
				shared_from_this(),
				boost::asio::placeholders::error,
				placeholders::bytes_transferred));
			if(m_ftask_ptr->transfertimes==msgrquestfile_->TransferTimes)
			{
				m_ftask_ptr->Finish();
				std::cout<<"写入文件完成"<<std::endl;
			}
		}
		break;
	default:
		break;
	}
}
