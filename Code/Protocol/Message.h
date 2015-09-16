#pragma once
#include <boost/smart_ptr.hpp>
#define MSGHEADLEN (8)

#ifdef _DLLEXPORT_Message
#define DLL_Message __declspec(dllexport)
#else
#define DLL_Message __declspec(dllimport)
#endif


namespace protocol
{
	enum Msgoffset
	{
		lengthoffset=0,
		typeoffset=4,
	};

	enum MsgType
	{
		msg_RequestSendFile,
		msg_WriteFile
	};

	typedef struct  
	{
		boost::shared_array<char> buf;
		unsigned int buflen;
	}MessageData;

	class  DLL_Message Message
	{
	protected:
		//协议体缓冲区大小
		boost::shared_array<char> msgbuf_;
		//消息指针的偏移
		int msgoffset_;
		//消息体长度
		int msgbodylen_;
	public:
		//消息类型
		MsgType msgtype_;
	public:
		Message();

		Message(int bodylen);

		~Message(void);

		//取得协议体的长度
		virtual char *GetBodyBuf();

		//取得消息体的长度
		virtual int GetMsgBufferLen()=0;

		//解析一次一次协议体
		virtual bool  HandleMsg(int bytestransfer)=0;

		//取得消息的字节
		virtual MessageData GetBytes()=0;

	};
}


