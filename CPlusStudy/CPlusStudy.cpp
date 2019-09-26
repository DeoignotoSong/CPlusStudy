// CPlusStudy.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <Windows.h>
#include <direct.h>
#include <queue>
#include "ThostFtdcMdApi.h"
#include "ThostFtdcTraderApi.h"
#include "Helper.h"
#include "Global.h"

using namespace std;

int main()
{
	Helper helper;
	// 保存生成的log文件的文件夹路径
	string logFilePath = helper.GetConfig("config", "LogFilesPath");
	string CallAuctionInstrumentsFilePath = helper.GetConfig("config", "CallAuctionInstrumentsFile");

	// 创建保存生成的log文件的文件夹
	// folderCreatedResult：
	// 0：创建成功
	// -1：文件夹存在，创建失败
	int folderCreatedResult = _mkdir(logFilePath.c_str());

	if (folderCreatedResult == 0) {
		cout << "Create log directory success." << endl;
	}
	else {
		cout << "Log directory is already existed." << endl;
	}

	helper.InitializeInstruments();

	for (auto &instrument: callAuctionInstruments) {
		cout << instrument.second.instrumentId << ": " << instrument.second.position << endl;
	}

	CThostFtdcTraderApi* mUser = CThostFtdcTraderApi::CreateFtdcTraderApi();
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
