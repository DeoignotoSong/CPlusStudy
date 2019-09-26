#pragma once
#include <string>
#include <map>

using namespace std;

struct Instrument
{
	// 合约号
	string instrumentId;
	// 交易所代码
	string exchangeCode;
	// 持仓
	int position;
	// 申买价一
	double bidPrice;
	// 申卖价一
	double adkPrice;
};

extern map<string, Instrument> callAuctionInstruments;
