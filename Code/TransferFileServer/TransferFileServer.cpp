// TransferFileServer.cpp : �������̨Ӧ�ó������ڵ㡣
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

