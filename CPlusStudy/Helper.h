#pragma once
#include <string>
#include <wtypes.h>
#include <conio.h>
#include <iostream>
#include <locale>
#include <string>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <sstream>
#include <locale.h>
#include <vector>
#include "Global.h"

using namespace std;

class Helper
{
public:
	std::string GetConfig(std::string title, std::string cfgName);
	void InitializeInstruments();
	vector<string> Split(const string& s, const string& c);
private:
	std::string CurPath();
};

