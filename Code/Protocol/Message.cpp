#include "stdafx.h"
#include "DLLAPI.h"
#include "Message.h"

using namespace protocol;


Message::Message():msgbuf_(nullptr),
	msgtype_(msg_RequestSendFile),
	msgoffset_(0),
	msgbodylen_(0)
{

}

Message::Message(int bodylen):msgbuf_(new char[bodylen]),
	msgtype_(msg_RequestSendFile),
	msgoffset_(0),
	msgbodylen_(bodylen)
{
}

Message::~Message(void)
{
}

char * protocol::Message::GetBodyBuf()
{
	char* buf= msgbuf_.get()+msgoffset_;
	return buf;
}












