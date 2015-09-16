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

		//��Ϣ��ʱָ��
		boost::shared_ptr<Message> msg_ptr_;

		//Э��ͷ�Ļ�������С
		boost::shared_array<char> msgheadbuf_;

	public:
		MessageFactory(void);

		~MessageFactory(void);

		//ȡ�ý����������ĳ���
		int GetMessageBufLen();

		//ȡ�ý���������
		char * GetMessageBuf();

		//������Ϣ
		void HandleMessage(int bytesnum);

		//������Ϣ�ɹ�
	    boost::function<void (boost::shared_ptr<protocol::Message>&)> ResolveMessage;
	};
}


