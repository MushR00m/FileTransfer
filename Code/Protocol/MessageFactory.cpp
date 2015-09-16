#include "stdafx.h"
#include "DLLAPI.h"
#include "Message.h"
#include "MessageFactory.h"
#include "RequestFileMessage.h"
#include "WrtieFileMessage.h"


using  namespace protocol;

MessageFactory::MessageFactory(void):msgheadbuf_(new char[MSGHEADLEN]),
	msg_ptr_(nullptr),
	state_(State::Resolvehead)
{
}

MessageFactory::~MessageFactory(void)
{
}

char * MessageFactory::GetMessageBuf()
{
	switch (state_)
	{
	case protocol::MessageFactory::Resolvehead:
		{
			return msgheadbuf_.get();
		}
		break;
	case protocol::MessageFactory::Resolvemsg:
		{
			return msg_ptr_->GetBodyBuf();
		}
		break;
	default:
		return nullptr;
		break;
	}
}

int MessageFactory::GetMessageBufLen()
{
	switch (state_)
	{
	case protocol::MessageFactory::Resolvehead:
		{
			return MSGHEADLEN;
		}
		break;
	case protocol::MessageFactory::Resolvemsg:
		{
			return msg_ptr_->GetMsgBufferLen();
		}
		break;
	default:
		return 0;
		break;
	}
}

void MessageFactory::HandleMessage(int bytesnum)
{
	switch (state_)
	{
	case MessageFactory::Resolvehead:
		{
			UINT32* tmp=reinterpret_cast<UINT32*>(msgheadbuf_.get());
			UINT32 bodylen=*tmp;//得出消息体的长度
			bodylen=bodylen-MSGHEADLEN;
			int* typetmp=reinterpret_cast<int*>(msgheadbuf_.get()+4);
			int type=*typetmp;
			switch (type)
			{
			case msg_RequestSendFile:
				{
					msg_ptr_=boost::shared_ptr<RequestFileMessage>(new RequestFileMessage(bodylen));
					msg_ptr_->msgtype_=msg_RequestSendFile;
					state_=MessageFactory::Resolvemsg;
				}
				break;
			case msg_WriteFile:
				{
					msg_ptr_=boost::shared_ptr<WrtieFileMessage>(new WrtieFileMessage(bodylen));
					msg_ptr_->msgtype_=msg_WriteFile;
					state_=MessageFactory::Resolvemsg;
				}
				break;
			default:
				break;
			}
		}
		break;
	case MessageFactory::Resolvemsg:
		{
			if (msg_ptr_->HandleMsg(bytesnum))
			{
				state_=MessageFactory::Resolvehead;
				
				if (!ResolveMessage.empty())
				{
					ResolveMessage(msg_ptr_);
				}
			}
		}
		break;
	}
}
