#pragma once
#include <string>
#include <map>

using namespace std;

struct Instrument
{
	// ��Լ��
	string instrumentId;
	// ����������
	string exchangeCode;
	// �ֲ�
	int position;
	// �����һ
	double bidPrice;
	// ������һ
	double adkPrice;
};

extern map<string, Instrument> callAuctionInstruments;