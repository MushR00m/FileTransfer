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
		//Э���建������С
		boost::shared_array<char> msgbuf_;
		//��Ϣָ���ƫ��
		int msgoffset_;
		//��Ϣ�峤��
		int msgbodylen_;
	public:
		//��Ϣ����
		MsgType msgtype_;
	public:
		Message();

		Message(int bodylen);

		~Message(void);

		//ȡ��Э����ĳ���
		virtual char *GetBodyBuf();

		//ȡ����Ϣ��ĳ���
		virtual int GetMsgBufferLen()=0;

		//����һ��һ��Э����
		virtual bool  HandleMsg(int bytestransfer)=0;

		//ȡ����Ϣ���ֽ�
		virtual MessageData GetBytes()=0;

	};
}


