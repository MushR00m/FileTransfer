#include "stdafx.h"
#include "DLLAPI.h"
#include "Message.h"
#include "RequestFileMessage.h"
#include <iostream>
#include <stdlib.h>
#include <string>
#include <errno.h>
using namespace protocol;


RequestFileMessage::RequestFileMessage():Message(),
	Filename()
{
}

RequestFileMessage::RequestFileMessage(int bodylen):
	Message(bodylen),
	Filename()
{
}

char * RequestFileMessage::GetBodyBuf()
{
	return this->msgbuf_.get()+msgoffset_;
}

int RequestFileMessage::GetMsgBufferLen()
{
	return msgbodylen_-msgoffset_;
}

MessageData RequestFileMessage::GetBytes()
{
	int len=16+Filename.length()+1;

	boost::shared_array<char> buf(new char[len]);
	ZeroMemory(buf.get(),len);

	int* lentmp=reinterpret_cast<int*>(buf.get());

	*lentmp=len;//协议头8个字节

	MsgType* msgtype=reinterpret_cast<MsgType*>(buf.get()+4);

	*msgtype=msg_RequestSendFile; //消息类型

	int* filenamelen=reinterpret_cast<int*>(buf.get()+8);
	*filenamelen=Filename.length()+1;

	std::strcpy(buf.get()+12,Filename.data());
	
    int* sendtimes=reinterpret_cast<int*>(buf.get()+12+Filename.length()+1);
	*sendtimes=TransferTimes;
	MessageData data;

	data.buf=buf;
	data.buflen=len;

	return data;
}

RequestFileMessage::~RequestFileMessage(void)
{
}

bool RequestFileMessage::HandleMsg(int bytestransfer)
{
	msgoffset_+=bytestransfer;
	if (msgbodylen_==msgoffset_) 
	{
		char *pbuf=msgbuf_.get();

		int* ptran_times=reinterpret_cast<int*>(pbuf+msgbodylen_-4);
		int* filenamelen=reinterpret_cast<int*>(pbuf);

		int len=*filenamelen;
		std::cout<<"文件名字长度"<<len<<std::endl;

		char* tmpbuf=new char[len+1];
		tmpbuf[len]='\0';
		memcpy(tmpbuf,pbuf+4,len);

		Filename=std::string(tmpbuf);
		delete[] tmpbuf;

		TransferTimes=*ptran_times;//传输次数
		std::cout<<"RequestFileMessage::HandleMsg 传输次数"<<TransferTimes<<std::endl;
		return true;
	}
	else
	{
		return false;
	}
}
