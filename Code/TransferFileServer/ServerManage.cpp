#include "stdafx.h"
#include "ServerManage.h"
#include <boost/asio.hpp>
#include <boost/smart_ptr.hpp>
#include <iostream>
#include <boost/bind.hpp>
#include "Session.h"
#include "SessionList.h"


ServerManage* ServerManage::m_Instance=nullptr;


ServerManage::ServerManage():acceptor_(ios_,tcp::endpoint(tcp::v4(),6688))
{
	shared_ptr<Session> new_session(new Session(ios_));
	acceptor_.async_accept(new_session->socket(),
		  boost::bind(&ServerManage::OnUserConnect,
		  this,
		  new_session,
		  placeholders::error)
		  );
}

ServerManage::ServerManage(const ServerManage& sm):acceptor_(ios_,tcp::endpoint(tcp::v4(),6688))
{

}

ServerManage::~ServerManage(void)
{

}

void ServerManage::Init()
{
	if (m_Instance==NULL)
	{
		m_Instance=new ServerManage();
	}
}


void ServerManage::OnUserConnect(shared_ptr<Session>& sess_ptr,const boost::system::error_code& error)
{
	if (!error)
	{
		std::cout<<"有新用户连接"<<std::endl;
		sess_ptr->start();//启动连接
		shared_ptr<Session> new_session(new Session(ios_));
		acceptor_.async_accept(new_session->socket(),
			boost::bind(&ServerManage::OnUserConnect,
			this,
			new_session,
			placeholders::error)
			);
	}
	else
	{
		
	}
}

void ServerManage::OnUserDisconnect(shared_ptr<ip::tcp::socket> usr)
{

}

ServerManage* ServerManage::GetInstance()
{
	if (m_Instance!=NULL)
	{
		return m_Instance;
	}
	else
	{
		m_Instance=new ServerManage();
		return m_Instance;
	}
}

void ServerManage::start()
{
	//设置最大的线程个数。  
	const int nMaxCount = 5;  
	//循环地创建N个线程。  
	for (int i = 0; i < nMaxCount; ++i)  
	{  
		m_Instance->m_threadgroup.create_thread(&ServerManage::Run);
	}  
}

void ServerManage::Run()
{
	m_Instance->ios_.run();
}
