#pragma once
#ifdef _DLL_EXPORT_RequestFileMessage
#define DLL_RequestFileMessage __declspec(dllexport)
#else
#define DLL_RequestFileMessage __declspec(dllimport)
#endif
#include <iostream>
namespace protocol
{
	class Message;

	class  DLL_RequestFileMessage RequestFileMessage:public Message
	{
	public:
		RequestFileMessage();

		RequestFileMessage(int bodylen);

		~RequestFileMessage(void);

		virtual bool  HandleMsg(int bytestransfer);

		//取得协议体的长度
		virtual char *GetBodyBuf();

		//取得消息体的长度
		virtual int GetMsgBufferLen();

		virtual MessageData GetBytes();

		int messagetype;

		//文件名
		std::string Filename;

		//文件大小
		unsigned long FileSize;

		//文件传输份数
		unsigned long TransferTimes;
		
	};
}


