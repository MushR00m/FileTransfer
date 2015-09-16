// TransferFileServer.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "ServerManage.h"
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	ServerManage::Init();
	ServerManage::start();

	std::system("pause");
	return 0;
}

