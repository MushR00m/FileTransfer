// ProtocolUnitTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include "..\Protocol\Message.h"
#include "..\Protocol\RequestFileMessage.h"
#include "..\Protocol\MessageFactory.h"
#include "..\Protocol\WrtieFileMessage.h"

using namespace protocol;
using namespace std;


void TestResolveMsgHeader()
{
	MessageFactory mf;

	char *headbuf=mf.GetMessageBuf();
	int headlen=mf.GetMessageBufLen();
	cout<<"协议头长度:"<<headlen<<endl;
	memset(headbuf,0x00,8);

	int *len=reinterpret_cast<int*>(headbuf);
	string filename="测试文件";

	*len=filename.length()+16; //

	MsgType type=msg_RequestSendFile;
	MsgType *tmptype=reinterpret_cast<MsgType*>(headbuf+4);
	*tmptype=type;
	mf.HandleMessage(8);

	headbuf=mf.GetMessageBuf();
	headlen=mf.GetMessageBufLen();

	int* filenamelen=reinterpret_cast<int*>(headbuf);
	*filenamelen=filename.length();

	memcpy(headbuf+4,filename.c_str(),filename.length());
	int *sendtimes=reinterpret_cast<int*>(headbuf+4+filename.length());
	*sendtimes=12;
	mf.HandleMessage(headlen);
}

void ResoloveMessage(boost::shared_ptr<Message> &msgptr)
{
     /*cout<<"msg"<<msgptr<<endl;*/
}

void TestMessageFactory()
{
	RequestFileMessage msg;
	msg.Filename="测试文件";
	msg.TransferTimes=12;

	boost::shared_array<char> buf=msg.GetBytes();
	char *tmp=buf.get();


	MessageFactory mf;
	mf.ResolveMessage=boost::bind(&ResoloveMessage,_1);
	char *target=mf.GetMessageBuf();
	int len=mf.GetMessageBufLen();
	cout<<"测试"<<endl;
	memcpy(target,tmp,8);
	mf.HandleMessage(8);
	target=mf.GetMessageBuf();
	len=mf.GetMessageBufLen();
	memcpy(target,tmp+8,len);
	mf.HandleMessage(len);
}

void TestWriteMessage()
{
	WrtieFileMessage msg;
	msg.packagebytesnum=packagelen;
	msg.packagenum=1;

	MessageData dat=msg.GetBytes();
	
	MessageFactory mf;
	char *targetbuf=mf.GetMessageBuf();
	int len=mf.GetMessageBufLen();
	memcpy(targetbuf,buf.get(),8);
	mf.HandleMessage(8);
	targetbuf=mf.GetMessageBuf();
	len=mf.GetMessageBufLen();
	memcpy(targetbuf,buf.get()+8,len);
	mf.HandleMessage(len);
}


int _tmain(int argc, _TCHAR* argv[])
{
	TestWriteMessage();
	return 0;
}

