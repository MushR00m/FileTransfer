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

		//ȡ��Э����ĳ���
		virtual char *GetBodyBuf();

		//ȡ����Ϣ��ĳ���
		virtual int GetMsgBufferLen();

		virtual MessageData GetBytes();

		int messagetype;

		//�ļ���
		std::string Filename;

		//�ļ���С
		unsigned long FileSize;

		//�ļ��������
		unsigned long TransferTimes;
		
	};
}


