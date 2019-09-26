#pragma  once
#include "Helper.h"

/*�������ƣ�getConfig()
�������ܣ���ȡ�����ļ�ini����Ӧ�����title��ָ�������ֶ�cfgname��ֵ
����1��string title		�����[***]
����2��string cfgName		������µ������ֶ�
����ֵ�������ļ�ini����Ӧ�����title��ָ�������ֶ�cfgname��ֵ
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
		if (strtmp.substr(0, 1) == "#")	continue;	//����ע��		
		if (flag == 0)
		{
			if (strtmp.find(title) != string::npos)
			{
				if (strtmp.substr(0, 1) == "[")
				{
					if (strtmp.find("]") == string::npos) 	break;	//ȱʧ��]���˳�
					strtitle = strtmp.substr(1);
					strtitle = strtitle.erase(strtitle.find("]"));
					if (strtitle == title)		//�ҵ���������ñ�־λΪ1�������Ͳ�������һ���������
					{
						flag = 1;
						continue;
					}
				}
			}
		}
		if (flag == 1)
		{
			if (strtmp.substr(0, 1) == "[")	break;	//���������һ��[]��˵����ǰ������Ӧ�������ֶ�������ϣ�����������
			if (strtmp.find(cfgName) != string::npos)
			{
				if (strtmp.find("=") == string::npos)	break;	//ȱʧ��=���˳�
				strcfgname = strtmp;
				strcfgname = strcfgname.erase(strcfgname.find("="));
				if (strcfgname == cfgName)		//�ҵ��������Ӧ���ֶκ󣬷���ֵ
				{
					returnValue = strtmp.substr(strtmp.find("=") + 1);
					return returnValue;
				}
				else continue;
			}
		}
	}
	cout << "�����ļ�����û�ҵ�" << title << "��Ӧ������" << cfgName << "��" << endl;

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