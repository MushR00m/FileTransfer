// UDPClientTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServerAgent.h"
#include <iostream>
#include <stdio.h>
using namespace  std;

void filesend_persent(float num)
{

}

int _tmain(int argc, _TCHAR* argv[])
{

	char a;
	scanf_s("%c",&a);
	cout<<a<<endl;

	switch (a)
	{
	case 'A':
		cout<<"test"<<endl;
		break;
	default:
		break;
	}
	//string serveraddress="127.0.0.1";
	//short s=6688;
	//ServerAgent serveragent(serveraddress,s);
	//string filename="E:\\安装包\\AdobePhotoshopCS6(64bit)Portable.zip";
	//serveragent.SendFile(filename,FileSendPercent(filesend_persent));
	std::system("pause");
	return 0;
}

