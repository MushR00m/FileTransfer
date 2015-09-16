#pragma once
#ifdef _DLL_EXPORT_WrtieFileMessage
#define DLL_WrtieFileMessage __declspec(dllexport)
#else
#define DLL_WrtieFileMessage __declspec(dllimport)
#endif
#define WriteFileMessagelen 8

#define  packagelen (1508336)
namespace protocol
{
	class Message;

	class DLL_WrtieFileMessage WrtieFileMessage:public Message
	{
	public:
		//当前的包的编号
		int packagenum;

		//当前的数据包种存放的数据的数量
		int packagebytesnum;

		WrtieFileMessage(void);

		WrtieFileMessage(int bodylen);

		~WrtieFileMessage(void);




		virtual bool  HandleMsg(int bytestransfer);

		//取得协议体的长度
		virtual char *GetBodyBuf();

		//取得消息体的长度
		virtual int GetMsgBufferLen();

		//去除消息当中的缓冲区
		char* GetData();
		//取得消息长度
		int GetDataLen();

		virtual  MessageData GetBytes();
	};
}


