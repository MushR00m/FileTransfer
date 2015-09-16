#include "stdafx.h"
#include "SessionList.h"
#include "Session.h"

SessionList::SessionList(void)
{

}


SessionList::~SessionList(void)
{

}

UINT SessionList::insert(boost::shared_ptr<ip::tcp::socket> usr)
{
	{
	  boost::mutex::scoped_lock lock(m_mutex);
	}
	return 0; 
}

boost::shared_ptr<Session> SessionList::findSessionById(UINT id)
{
	{
		boost::mutex::scoped_lock lock(m_mutex);
	}
	shared_ptr<Session> ptr;
	return ptr;
}
