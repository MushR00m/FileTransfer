#pragma once
#include <boost/noncopyable.hpp>
#include <boost/smart_ptr.hpp>
#include <boost/function.hpp>
#include <boost/bind.hpp>
#ifdef _DLL_EXPORT_RequestFileMessage
#define DLL_MessageFactory __declspec(dllexport)
#else
#define DLL_MessageFactory __declspec(dllimport)
#endif
#define MSGHEADLEN (8)


namespace protocol
{
	class Message;
	class  DLL_MessageFactory MessageFactory:private boost::noncopyable
	{
		enum  State
		{
			Resolvehead,
			Resolvemsg
		};

		State state_;

		//消息临时指针
		boost::shared_ptr<Message> msg_ptr_;

		//协议头的缓冲区大小
		boost::shared_array<char> msgheadbuf_;

	public:
		MessageFactory(void);

		~MessageFactory(void);

		//取得解析缓冲区的长度
		int GetMessageBufLen();

		//取得解析缓冲区
		char * GetMessageBuf();

		//解析消息
		void HandleMessage(int bytesnum);

		//解析消息成功
	    boost::function<void (boost::shared_ptr<protocol::Message>&)> ResolveMessage;
	};
}


