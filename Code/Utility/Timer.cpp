#include "stdafx.h"
#include "DLLExports.h"
#include "Timer.h"
#include <boost/thread.hpp>
#include <boost/bind.hpp>
using namespace Utility;
Timer::Timer(void):m_ios(),
	time_work(false)
{

}


Timer::~Timer(void)
{
}

void Utility::Timer::Start()
{
	time_work=true;
	boost::thread timethread(boost::bind(&Timer::TimeWork,shared_from_this()));
}

void Utility::Timer::Stop()
{
	time_work=false;
}

Utility::Timer::Timer(const Timer& timer)
{
	
	
}

Timer& Utility::Timer::operator=(const Timer& t)
{

}

void Utility::Timer::TimeWork()
{
	while (time_work)
	{
		if (!Elipse.empty())
		{
			Elipse();
		}
	}
}
