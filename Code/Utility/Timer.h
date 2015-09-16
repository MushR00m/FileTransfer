#pragma once
#ifdef _DLLEXPORT_Timer
#define DLL_Timer __declspec(dllexport)
#else
#define DLL_Timer __declspec(dllimport)
#endif


#include <boost/smart_ptr.hpp>
#include <boost/asio.hpp>
#include <boost/function.hpp>
namespace Utility
{
	typedef boost::function<void()> OnTime;

	class DLL_Timer Timer:public boost::enable_shared_from_this<Timer>
	{
	private:
		bool time_work;

		boost::asio::io_service m_ios;
	public:
		OnTime Elipse;

		Timer(void);

		~Timer(void);

		void Start();

		void Stop();
	private:

		Timer(const Timer& timer);

		Timer& operator=(const Timer& t);

		void TimeWork();
	};
}


