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
		//��ǰ�İ��ı��
		int packagenum;

		//��ǰ�����ݰ��ִ�ŵ����ݵ�����
		int packagebytesnum;

		WrtieFileMessage(void);

		WrtieFileMessage(int bodylen);

		~WrtieFileMessage(void);




		virtual bool  HandleMsg(int bytestransfer);

		//ȡ��Э����ĳ���
		virtual char *GetBodyBuf();

		//ȡ����Ϣ��ĳ���
		virtual int GetMsgBufferLen();

		//ȥ����Ϣ���еĻ�����
		char* GetData();
		//ȡ����Ϣ����
		int GetDataLen();

		virtual  MessageData GetBytes();
	};
}


