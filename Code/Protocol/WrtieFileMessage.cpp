#include "stdafx.h"
#include "DLLAPI.h"
#include "Message.h"
#include "WrtieFileMessage.h"
#include <boost/smart_ptr.hpp>

using namespace protocol;

WrtieFileMessage::WrtieFileMessage(int bodylen):Message(bodylen),
	packagenum(0),
	packagebytesnum(bodylen-WriteFileMessagelen)
{
	msgtype_=msg_WriteFile;
}

WrtieFileMessage::WrtieFileMessage(void)
{
}

WrtieFileMessage::~WrtieFileMessage(void)
{
}

bool WrtieFileMessage::HandleMsg(int bytestransfer)
{
	msgoffset_+=bytestransfer;
	if (msgoffset_==msgbodylen_)
	{
		int* tmp=reinterpret_cast<int*>(msgbuf_.get());
		
		packagenum=*tmp;
		return true;
	}
	return false;
}

char * WrtieFileMessage::GetBodyBuf()
{
	return msgbuf_.get()+msgoffset_;
}

int WrtieFileMessage::GetMsgBufferLen()
{
	return msgbodylen_-msgoffset_;
}


MessageData WrtieFileMessage::GetBytes()
{
	boost::shared_array<char> buf(new char[packagebytesnum+WriteFileMessagelen+MSGHEADLEN]);
	ZeroMemory(buf.get(),packagebytesnum+WriteFileMessagelen+MSGHEADLEN);

	int *plen=reinterpret_cast<int*>(buf.get());
	*plen=packagebytesnum+WriteFileMessagelen+MSGHEADLEN;
	MsgType* t=reinterpret_cast<MsgType*>(buf.get()+4);
	*t=msg_WriteFile;
	int*pnum=reinterpret_cast<int*>(buf.get()+8);
	*pnum=packagenum;

	MessageData data;
	data.buf=buf;
	data.buflen=*plen;
	return data;
}


char* WrtieFileMessage::GetData()
{
	return msgbuf_.get()+WriteFileMessagelen;
}

int WrtieFileMessage::GetDataLen()
{
	return packagebytesnum;
}
