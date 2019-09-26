#pragma  once
#include "Helper.h"

/*函数名称：getConfig()
函数功能：获取配置文件ini中相应大标题title下指定配置字段cfgname的值
参数1：string title		大标题[***]
参数2：string cfgName		大标题下的配置字段
返回值：配置文件ini中相应大标题title下指定配置字段cfgname的值
*/
std::string Helper::GetConfig(std::string title, std::string cfgName)
{
	string curpath = this->CurPath();
	const char* INIFile = "config.ini";
	ifstream inifile(INIFile);
	if (!inifile.is_open())
	{
		cerr << "Could not open " << INIFile << endl;
		inifile.clear();

		exit(-1);
	}
	string strtmp, strtitle, strcfgname, returnValue;
	int flag = 0;
	while (getline(inifile, strtmp, '\n'))
	{
		if (strtmp.substr(0, 1) == "#")	continue;	//过滤注释		
		if (flag == 0)
		{
			if (strtmp.find(title) != string::npos)
			{
				if (strtmp.substr(0, 1) == "[")
				{
					if (strtmp.find("]") == string::npos) 	break;	//缺失“]”退出
					strtitle = strtmp.substr(1);
					strtitle = strtitle.erase(strtitle.find("]"));
					if (strtitle == title)		//找到大标题设置标志位为1，这样就不再找下一个大标题了
					{
						flag = 1;
						continue;
					}
				}
			}
		}
		if (flag == 1)
		{
			if (strtmp.substr(0, 1) == "[")	break;	//如果遇到下一个[]号说明当前大标题对应的配置字段搜索完毕，结束搜索。
			if (strtmp.find(cfgName) != string::npos)
			{
				if (strtmp.find("=") == string::npos)	break;	//缺失“=”退出
				strcfgname = strtmp;
				strcfgname = strcfgname.erase(strcfgname.find("="));
				if (strcfgname == cfgName)		//找到大标题相应的字段后，返回值
				{
					returnValue = strtmp.substr(strtmp.find("=") + 1);
					return returnValue;
				}
				else continue;
			}
		}
	}
	cout << "配置文件错误：没找到" << title << "对应配置项" << cfgName << "！" << endl;

	exit(-1);
}

void Helper::InitializeInstruments()
{
	string callAuctionInstrumentsFilePath = this->GetConfig("config", "CallAuctionInstrumentsFile");
	char buffer[256];
	ifstream in(callAuctionInstrumentsFilePath);

	if (!in.is_open()) {
		cout << "Appear error when opening instruments_1.ini file." << endl;

		exit(1);
	}
	else
	{
		cout << "Open file success." << endl;
	}

	while (!in.eof())
	{
		in.getline(buffer, 100);
		string line = buffer;
		vector<string> instrumentsProperties = this->Split(line, ",");
		Instrument currentInstrument;
		currentInstrument.instrumentId = instrumentsProperties[1];
		currentInstrument.position = stoi(instrumentsProperties[2]);
		callAuctionInstruments[instrumentsProperties[1]] = currentInstrument;
	}
}

vector<string> Helper::Split(const string& s, const string& c)
{
	vector<string> v;
	string::size_type pos1, pos2;
	pos2 = s.find(c);
	pos1 = 0;
	while (std::string::npos != pos2)
	{
		v.push_back(s.substr(pos1, pos2 - pos1));

		pos1 = pos2 + c.size();
		pos2 = s.find(c, pos1);
	}
	if (pos1 != s.length())
		v.push_back(s.substr(pos1));

	return v;
}

std::string Helper::CurPath()
{
	LPWSTR buffer = new wchar_t[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	wstring ws(buffer);
	string str = string(ws.begin(), ws.end());
	string::size_type pos = str.find_last_of("\\/");
	return str.substr(0, pos);
}
